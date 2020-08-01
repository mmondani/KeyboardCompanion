
$(document).ready(function() {
    let wifiSsid;
    let wifiPass;

    $("#ssid_loading").show();
    $("#refresh_button").hide();
    $("#ssid_list").hide();

    /*
    addSsisItem("SSID Prueba 1", -50);
    addSsisItem("SSID Prueba 2", -80);
    addSsisItem("SSID Prueba 3", -101);
    */

    askForSsids();

    $("#refresh_button").click(function() {
        askForSsids();

        $("#ssid_loading").show();
        $("#refresh_button").hide();
        $("#ssid_list").hide();
    });

    // Se debe asignar el evento click de esta forma para que se le 
    // asigne a elementos que se crean dinámicamente
    $(document).on("click", ".ssid_container", function() {
        wifiSsid = $(this).children(".wifi_ssid").html();

        $(".wifi_pass").remove();

        let inputChild = 
            `<div class="wifi_pass"> 
                <input type="text" id="wifi_pass" placeholder="Password">
                <input type="submit" id="passSubmit" value="Conectar">
            </div>
            `;

        $(inputChild).insertAfter(this);
    });


    $(document).on("click", "#passSubmit", function() {
        wifiPass = $("#wifi_pass").val();

        if (!wifiPass) 
            alert("Ingrese un password");
        else
        {      
            let xhttp = new XMLHttpRequest();
        
            xhttp.open("POST", `/connect?ssid=${wifiSsid}&pass=${wifiPass}`, true);
            xhttp.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
            xhttp.send();
        }
    });
});


function askForSsids( ) {
    let xhttp = new XMLHttpRequest();

    xhttp.onreadystatechange = function() {

        if (this.readyState == 4 && this.status == 200) {

            $("#refresh_button").show();
            $("#ssid_list").show();
            $("#ssid_loading").hide();

            let responseSsids = this.responseText.split(";").filter(i => i)

            $("#ssid_list").empty();
            for (let i = 0; i < responseSsids.length; i+=2) {
                
                let rssi = parseInt(responseSsids[i+1])
                
                addSsisItem(responseSsids[i], rssi);
            }
        }
    }

    xhttp.open("GET", "/ssids", true);
    xhttp.send();
}


function addSsisItem (name, rssi) {

    let signalLevel = 0;
    if (rssi > -75)
        signalLevel = 3;
    else if (rssi > -80)
        signalLevel = 2; 
    else if (rssi > -90)
        signalLevel = 1;
    
    

    let newChild = 
            `<div class="ssid_container">
                <div class="wifi_ssid">${name}</div>
                <img class="wifi_signal" src="signal${signalLevel}.png" width="30" height="30" >
            </div>`;

    $("#ssid_list").append(newChild);
}
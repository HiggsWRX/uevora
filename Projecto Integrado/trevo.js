function createMap21() {
    var map;
    var paragemLuis = new google.maps.LatLng(38.572859, -7.910755);
    var estacao = new google.maps.LatLng(38.567787, -7.918346);

    var carreira21paragem1 = new google.maps.LatLng(38.583720, -7.912567);

    // Google maps para a carreira 21
    var mapProp = {
        center: new google.maps.LatLng(38.5697999, -7.9149639),
        zoom: 16,
        mapTypeId: google.maps.MapTypeId.ROADMAP
    };
    map = new google.maps.Map(document.getElementById("googleMap1"), mapProp);

    var marker = new google.maps.Marker({
        position: paragemLuis,
        title: "Largo Luis de Camões"
    });
    marker.setMap(map);

    var marker = new google.maps.Marker({
        position: estacao,
        title: "Estação de Autocarros"
    });
    marker.setMap(map);

    var marker = new google.maps.Marker({
        position: carreira21paragem1,
        title: "Bairro do Granito"
    });
    marker.setMap(map);

    google.maps.event.trigger(map, "resize");

    var bounds = new google.maps.LatLngBounds();
    bounds.extend(estacao);
    bounds.extend(carreira21paragem1);
    bounds.extend(paragemLuis);
    map.fitBounds(bounds);
}

$("#carreira21mapa").on("shown.bs.modal", createMap21);

function createMap22() {
    var map;
    var paragemLuis = new google.maps.LatLng(38.572859, -7.910755);
    var estacao = new google.maps.LatLng(38.567787, -7.918346);
    var carreira22paragem1 = new google.maps.LatLng(38.610696, -7.899541);

    // Google maps para a carreira 22
    var mapProp = {
        center: new google.maps.LatLng(38.5697999, -7.9149639),
        zoom: 16,
        mapTypeId: google.maps.MapTypeId.ROADMAP
    };
    map = new google.maps.Map(document.getElementById("googleMap2"), mapProp);

    var marker = new google.maps.Marker({
        position: paragemLuis,
        title: "Largo Luis de Camões"
    });
    marker.setMap(map);

    var marker = new google.maps.Marker({
        position: estacao,
        title: "Estação de Autocarros"
    });
    marker.setMap(map);
    
    var marker = new google.maps.Marker({
        position: carreira22paragem1,
        title: "Canaviais"
    });
    marker.setMap(map);

    google.maps.event.trigger(map, "resize");

    var bounds = new google.maps.LatLngBounds();
    bounds.extend(estacao);
    bounds.extend(paragemLuis);
    bounds.extend(carreira22paragem1)
    map.fitBounds(bounds);
}

$("#carreira22mapa").on("shown.bs.modal", createMap22);

function createMap31() {
    var map;
    var paragemLuis = new google.maps.LatLng(38.572859, -7.910755);
    var estacao = new google.maps.LatLng(38.567787, -7.918346);
    var carreira31paragem1 = new google.maps.LatLng(38.569769, -7.923109);

    // Google maps para a carreira 31
    var mapProp = {
        center: new google.maps.LatLng(38.5697999, -7.9149639),
        zoom: 16,
        mapTypeId: google.maps.MapTypeId.ROADMAP
    };
    map = new google.maps.Map(document.getElementById("googleMap3"), mapProp);

    var marker = new google.maps.Marker({
        position: paragemLuis,
        title: "Largo Luis de Camões"
    });
    marker.setMap(map);

    var marker = new google.maps.Marker({
        position: estacao,
        title: "Estação de Autocarros"
    });
    marker.setMap(map);
    
    var marker = new google.maps.Marker({
        position: carreira31paragem1,
        title: "Malagueira"
    });
    marker.setMap(map);

    google.maps.event.trigger(map, "resize");

    var bounds = new google.maps.LatLngBounds();
    bounds.extend(estacao);
    bounds.extend(paragemLuis);
    bounds.extend(carreira31paragem1);
    map.fitBounds(bounds);
}

$("#carreira31mapa").on("shown.bs.modal", createMap31);

function createMap33() {
    var map;
    var paragemLuis = new google.maps.LatLng(38.572859, -7.910755);
    var estacao = new google.maps.LatLng(38.567787, -7.918346);
    var carreira33paragem1 = new google.maps.LatLng(38.572223, -7.896854);

    // Google maps para a carreira 33
    var mapProp = {
        center: new google.maps.LatLng(38.5697999, -7.9149639),
        zoom: 16,
        mapTypeId: google.maps.MapTypeId.ROADMAP
    };
    map = new google.maps.Map(document.getElementById("googleMap4"), mapProp);

    var marker = new google.maps.Marker({
        position: paragemLuis,
        title: "Largo Luis de Camões"
    });
    marker.setMap(map);

    var marker = new google.maps.Marker({
        position: estacao,
        title: "Estação de Autocarros"
    });
    marker.setMap(map);
    
    var marker = new google.maps.Marker({
        position: carreira33paragem1,
        title: "Sra da Saúde"
    });
    marker.setMap(map);

    google.maps.event.trigger(map, "resize");

    var bounds = new google.maps.LatLngBounds();
    bounds.extend(estacao);
    bounds.extend(paragemLuis);
    bounds.extend(carreira33paragem1);
    map.fitBounds(bounds);
}

$("#carreira33mapa").on("shown.bs.modal", createMap33);
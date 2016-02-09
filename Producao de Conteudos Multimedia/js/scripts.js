/*jslint plusplus: true*/

// Variables to keep track of various things, such as
// ammount of cash, assets unlocked, assets cost, etc

var kps = 0;
var numKs = 0;
var cash = 0;

//assets
var elder = {
    id: 1,
    name: "Friendly Elder",
    num: 0,
    unlocked: false,
    cost: 15,
    kps: 1
};
var kid = {
    id: 2,
    name: "Kid",
    num: 0,
    unlocked: false,
    cost: 100,
    kps: 5
};
var student = {
    id: 3,
    name: "CS Student",
    num: 0,
    unlocked: false,
    cost: 500,
    kps: 40
};
var contractor = {
    id: 4,
    name: "Contractor",
    num: 0,
    unlocked: false,
    cost: 3000,
    kps: 100
};
var champion = {
    id: 5,
    name: "Typewritting Champion",
    num: 0,
    unlocked: false,
    cost: 10000,
    kps: 400
};
var robot = {
    id: 6,
    name: "Robot",
    num: 0,
    unlocked: false,
    cost: 40000,
    kps: 1000
};

// upgrades

var elderUpgrade = {
    id: 1,
    name: "Nurse's help",
    unlocked: false,
    cost: 200,

}

//Using real times
var before = new Date();

function updateAsset(asset) {
    if (!asset.unlocked && cash >= asset.cost) {
        document.getElementById('noneUnlocked').style.display = 'none';

        var assetDiv = document.createElement('div');
        assetDiv.className = 'col-md-12 border-bot';
        assetDiv.style.color = '#c9c9c9';
        assetDiv.innerHTML = '<span>' + asset.name + '</span><span class="pull-right">You have <span id="num-' + asset.id + '">' + asset.num + '</span></span>' +
            '</br><img src="images/' + asset.id + '.png" height="30px">&nbsp;&nbsp;&nbsp;' +
            ' <img src="images/dollar.png" height="20px"> <span id="' + asset.id + '-price">' + asset.cost + '</span>' +
            '<button class="btn btn-success btn-sm pull-right" id="hire-' +asset.id + '">Buy 1</button></br></br>';

        document.getElementById('assets-tab').appendChild(assetDiv);

        // Temporary dividers are required to keep border bottoms, without them the page looks strange
        var tempDivider = document.createElement('div');
        tempDivider.className = 'col-md-12 border-top-light';
        document.getElementById('assets-tab').appendChild(tempDivider);

        // when the user buys the asset, update the number owned, its new price and deduct the cash
        document.getElementById('hire-' + asset.id).addEventListener('click', function (event) {
            if (cash >= asset.cost) {
                asset.num++;
                cash -= asset.cost;
                asset.cost = Math.ceil(asset.cost * 1.1);
                kps += asset.kps;
            }
        });

        asset.unlocked = true;

    } else if (asset.unlocked) {
        document.getElementById(asset.id + '-price').textContent = asset.cost;
        document.getElementById('num-' + asset.id).textContent = asset.num;
        document.getElementById('hire-' + asset.id).disabled = cash < asset.cost;
    }
};

function updateUpgrade(upgrade) {
    if (!upgrade.unlocked && cash >= upgrade.cost) {
        document.getElementById('noUpgrades').style.display = 'none';

        var upgradeDiv = document.createElement('div');
        upgradeDiv.className = 'col-md-12 border-bot';
        upgradeDiv.style.color = '#c9c9c9';
        upgradeDiv.innerHTML = '</br><button class="btn btn-success btn-sm pull-right" id="buy-'
            + upgrade.id +'">Buy Upgrade</button></br></br>';

        document.getElementById('upgrades-tab').appendChild(upgradeDiv);

        var tempDivider = document.createElement('div');
        tempDivider.className = 'col-md-12 border-top-light';
        document.getElementById('assets-tab').appendChild(tempDivider);

        document.getElementById('buy-' + upgrade.id).addEventListener('click', function (event) {
            if (cash >= upgrade.cost) {
                cash -= upgrade.cost;
            }
        });

        upgrade.unlocked = true;
    } else if (upgrade.unlocked) {

    }

};

// increase the number of keystrokes when user presses a key
// between a and z
document.addEventListener('keyup', function (event) {
    if (event.keyCode >= 65 && event.keyCode <= 90) {
        cash++;
        Typer.addText(event);
        var snd = new Audio("sounds/1.mp3");
        snd.volume = .2;
        snd.play();
    }
});

/*
            var randomnumber = Math.floor(Math.random() * (2 - 0 + 1)) + 0;
            var snd = keys[randomnumber];
            snd.volume = .5;
            snd.play();

            keyCounter++;
            if (keyCounter > 2) {
                keyCounter = 0;
            }

*/

// update the UI every 10 ms
window.setInterval(function () {
    now = new Date();
    var elapsedTime = (now.getTime() - before.getTime());

    updateAsset(elder);
    updateAsset(kid);
    updateAsset(student);
    updateAsset(contractor);
    updateAsset(champion);
    updateAsset(robot);

    updateUpgrade(elderUpgrade);

    document.getElementById("ks-count").textContent = kps;

    cash += (kps * elapsedTime / 1000);

    document.getElementById("cash").textContent = Math.floor(cash);

    before = now;

}, 10);

/* TERMINAL */
var Typer = {
    text: null,
    start: 0,
    index: 67,
    speed: 3,
    file: "",
    init: function () {
        accessCountimer = setInterval(function () {
            Typer.updateCursor();
        }, 500);
        $.get(Typer.file, function (data) {
            Typer.text = data;
        });
    },

    content: function () {
        return $("#console").html();
    },

    write: function (str) {
        $("#console").append(str);
        return false;
    },

    addText: function (key) {
        if (Typer.text) {
            var cont = Typer.content();
            if (cont.substring(cont.length - 1, cont.length) === "█") {
                $("#console").html($("#console").html().substring(0, cont.length - 1));
            }
            Typer.index += Typer.speed;
            var text = $("<div/>").text(Typer.text.substring(Typer.start, Typer.index)).html();

            var count = (text.match(/\n/g) || []).length;

            var rtn = new RegExp("\n", "g");
            var rts = new RegExp("\\s", "g");
            var rtt = new RegExp("\\t", "g");
            $("#console").html(text.replace(rtn, "<br/>").replace(rtt, "&nbsp;&nbsp;&nbsp;&nbsp;").replace(rts, "&nbsp;"));
            if (count > 14) {
                $("#console").empty();
                Typer.start = Typer.index;
                var returnSound = new Audio("sounds/return.wav");
                returnSound.volume = .1;
                returnSound.play();
                var bellSound = new Audio("sounds/bell.wav");
                bellSound.volume = .2;
                setTimeout(function(){ bellSound.play(); }, 1000);
            }
        }
    },

    updateCursor: function () {
        var cont = this.content();
        if (cont.substring(cont.length - 1, cont.length) === "█") {
            $("#console").html($("#console").html().substring(0, cont.length - 1));
        } else {
            this.write("█");
        }
    }
};

/* other js */

$(document).ready(function(){
    $('[data-toggle="popover"]').popover();
});



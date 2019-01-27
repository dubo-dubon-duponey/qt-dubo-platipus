var displayLibInfo = function(e){
    // Display library information
    var disp = e.API.root;
    var iNode = document.getElementById("info");
    var list = ["NAME", "VENDOR", "VERSION", "REVISION", "CHANGESET", "BUILD", "LINK", "QT", "PLUGIN_NAME", "PLUGIN_VERSION", "PLUGIN_REVISION"];

    list.forEach(function(i){
        var line = document.createElement("div");
        line.appendChild(document.createTextNode(i + ": " + disp[i]));
        iNode.appendChild(line)
    });
};

var powerManagerDemo = function(e){
    // Power manager API
    var setState = function(){
        var ps = document.getElementById('powermanagerState');
        var state;
        switch(e.API.powerManager.state){
            case e.API.powerManager.NONE:
                state = "NONE";
            break;
            case e.API.powerManager.SYSTEM:
                state = "SYSTEM";
            break;
            case e.API.powerManager.SCREEN:
                state = "SCREEN";
            break;
        }
        ps.innerHTML = "Current state: " + state;
    };

    setState();

    e.API.powerManager.stateChanged.connect(setState);

    var rem = document.getElementById("powermanagerNONE");
    rem.removeAttribute("disabled");
    rem.onclick = function(){
        e.API.powerManager.setState(e.API.powerManager.NONE, "Whatever reason to set to none!");
    };

    rem = document.getElementById("powermanagerSCREEN");
    rem.removeAttribute("disabled");
    rem.onclick = function(){
        e.API.powerManager.setState(e.API.powerManager.SCREEN, "Whatever reason to set to screen!");
    };

    rem = document.getElementById("powermanagerSYSTEM");
    rem.removeAttribute("disabled");
    rem.onclick = function(){
        e.API.powerManager.setState(e.API.powerManager.SYSTEM, "Whatever reason to set to system!");
    };
};

var appUtilsDemo = function(e){
    // AppUtils API
    var setDims = function(){
        var ps = document.getElementById("apputilsDimensions");
        ps.innerHTML = "x: " + e.API.appUtils.screenx + " - y:" + e.API.appUtils.screeny + " - w:" + e.API.appUtils.screenw + " - h:" + e.API.appUtils.screenh
        + " - rx:" + e.API.appUtils.renderx + " - ry:" + e.API.appUtils.rendery + " - rw:" + e.API.appUtils.renderw + " - rh:" + e.API.appUtils.renderh;
    };

    setDims();

    e.API.appUtils.updated.connect(setDims);

    rem = document.getElementById("dobadge");
    rem.removeAttribute("disabled");
    rem.onclick = function(){
        e.API.appUtils.badge(document.getElementById("badgetext").value);
    };

    rem = document.getElementById("doannoy");
    rem.removeAttribute("disabled");
    rem.onclick = function(){
        setTimeout(e.API.appUtils.annoy, 5000);
    };

    var setWindow = function(){
        var ps = document.getElementById("MV");
        ps.innerHTML = "Is movable? " + e.API.window.moveable;
        ps = document.getElementById("SH");
        ps.innerHTML = "Shadow? " + e.API.window.shadow;
        ps = document.getElementById("AL");
        ps.innerHTML = "Alpha? " + e.API.window.alpha;
        ps = document.getElementById("FS");
        ps.innerHTML = "Fullscreen? " + e.API.window.fullscreen;

        e.API.window.shouldMinimizeOnDoubleClick(function(data){
            ps = document.getElementById("shouldMinimizeOnDoubleClick");
            ps.innerHTML = "shouldMinimizeOnDoubleClick? " + data;
        });

        e.API.window.isDarkMode(function(data){
            ps = document.getElementById("isDarkMode");
            ps.innerHTML = "isDarkMode? " + data;
        });

        e.API.window.accentColor(function(data){
            ps = document.getElementById("accentColor");
            ps.innerHTML = "accentColor? " + data;
        });
    };

    setWindow();
    e.API.window.updated.connect(setWindow);

    rem = document.getElementById("dofs");
    rem.removeAttribute("disabled");
    rem.onclick = function(){
        e.API.window.fullscreen = ! e.API.window.fullscreen;
    };


    rem = document.getElementById("domv");
    rem.removeAttribute("disabled");
    rem.onclick = function(){
        e.API.window.moveable = ! e.API.window.moveable;
    };

    rem = document.getElementById("dosh");
    rem.removeAttribute("disabled");
    rem.onclick = function(){
        e.API.window.shadow = ! e.API.window.shadow;
    };

    rem = document.getElementById("doal");
    rem.removeAttribute("disabled");
    rem.onclick = function(){
        e.API.window.alpha = document.getElementById("alvalue").value;
    };

    document.getElementById("draggable").addEventListener("mouseover", function(){
        e.API.window.moveable = true;
    });
    document.getElementById("draggable").addEventListener("mouseout", function(){
        e.API.window.moveable = false;
    });
};

const imageURI = "https://avatars1.githubusercontent.com/u/19539395?s=100&amp;v=4";

// XXX toggable menu item are changing value AFTER being triggered
var menuDemo = function(e){
    e.API.menu.addMenu(function(menu){
        menu.title = "Main menu";

        menu.addAction(menu.NOROLE, function(action){
            console.warn("Action icon is" + action.icon);
            action.title = "NOROLE∞";
            action.icon.URI = imageURI;
            action.checkable = true;
            action.checked = true;
            action.shortcut = "CTRL+P";
            action.autoRepeat = true;
            action.updated.connect(function(data){
                console.warn("UPDATED" + action.checked);
            });
            action.triggered.connect(function(data){
                console.warn("TRIGGERED" + action.checked);
            });
        });
        menu.addAction(menu.TEXT, function(action){
            console.warn("Action is" + action);
            action.title = "TEXT∞";
            action.icon.URI = imageURI;
            action.checkable = true;
            action.checked = true;
            action.shortcut = "CTRL+O";
            action.autoRepeat = false;
            console.warn("action.autoRepeat" + action.autoRepeat);
        });
        menu.addAction(menu.APPLICATION, function(action){
            console.warn("Action is" + action);
            action.title = "APPLICATION∞";
            action.icon.URI = imageURI;
            action.checkable = true;
            action.checked = true;
        });
        menu.addAction(menu.ABOUTQT, function(action){
            console.warn("Action is" + action);
            action.title = "ABOUTQT∞";
            action.icon.URI = imageURI;
            action.checkable = true;
            action.checked = true;
        });
        menu.addAction(menu.ABOUT, function(action){
            console.warn("Action is" + action);
            action.title = "ABOUT∞";
            action.icon.URI = imageURI;
            action.checkable = true;
            action.checked = true;
        });
        menu.addAction(menu.PREFERENCES, function(action){
            console.warn("Action is" + action);
            action.title = "PREFERENCES∞";
            action.icon.URI = imageURI;
            action.checkable = true;
            action.checked = true;
        });
        menu.addAction(menu.QUIT, function(action){
            console.warn("Action is" + action);
            action.title = "QUIT∞";
            action.icon.URI = imageURI;
            action.checkable = true;
            action.checked = true;
        });

        menu.addMenu(function(sub){
            sub.title = "Sub Menu";
            sub.icon.URI = imageURI;
            sub.checkable = true;
            sub.checked = true;
        });
    });
};

var trayDemo = function(e){
    e.API.tray.menu.addMenu(function(menu){
        menu.title = "Submenu";
    });
    e.API.tray.menu.addAction(e.API.tray.menu.NOROLE, function(action){
        action.title = "Action";
    });
    e.API.tray.icon.URI = imageURI;
    e.API.tray.tooltip = "Foo foo";
    e.API.tray.visible = true;

    e.API.tray.activated.connect(function(reason){
        console.warn("Been activated with reason" + reason);
    });
};

window.addEventListener("roxee", function(e){
    displayLibInfo(e);
    powerManagerDemo(e);
    appUtilsDemo(e);
    menuDemo(e);
    trayDemo(e);
});

window.addEventListener("load", function(){
    return new QWebChannel(qt.webChannelTransport, function(channel){
        var e = new Event("roxee");
        window.Dubo = window.Dubo || {};
        e.API = window.Dubo["platipus"] = {
            root: channel.objects.Root,
            powerManager: channel.objects.PowerManager,
            appUtils: channel.objects.AppUtils,
            window: channel.objects.Window,
            menu: channel.objects.MenuBar,
            tray: channel.objects.Tray,
        };
        window.dispatchEvent(e);
    });
});


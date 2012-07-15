(function () {
    var MarkCell = function (options) {
            var height = options.height,
                width = options.width,
                context = options.context,

                SIZE = 4,
                ALIVE_COLOUR = "#cc3366",
                DEAD_COLOUR = "#acc8ac",

                drawAtWithColour = function (colour) {
                    return function (coordinates) {
                        var x = coordinates[0],
                            y = coordinates[1],
                            x1 = x * SIZE + width / 2 + SIZE / 2,
                            y1 = y * SIZE + height / 2 + SIZE / 2;

                        context.fillStyle = colour;
                        context.fillRect(x1, y1, SIZE - 1, SIZE - 1);
                    };
                };

            return {
                aliveAt: drawAtWithColour(ALIVE_COLOUR),
                deadAt: drawAtWithColour(DEAD_COLOUR)
            };
    };

    var Game = function (options) {
        var selectors = options.selectors,
            urls = options.urls,
            displayUrl = urls.display,
            tickUrl = urls.tick,
            markCell = undefined,

            WIDTH = 1280,
            HEIGHT = 800,
            TIME_INTERVAL = 1000,

            initialize = function () {
                var canvas = document.getElementById(selectors.world)
                    context = canvas.getContext('2d');
                markCell = new MarkCell({
                    context: context,
                    width: WIDTH,
                    height: HEIGHT
                });
            },

            fetchWorld = function () {
                var request = new XMLHttpRequest();
                request.open("GET", displayUrl, false);
                request.send();
                return JSON.parse(request.responseText)['world'];
            },

            tick = function () {
                var request = new XMLHttpRequest();
                request.open("POST", tickUrl, false);
                request.send();
            },

            render = function () {
                var world = fetchWorld();
                world.previous.forEach(function (coordinates) {
                    markCell.deadAt(coordinates);
                });
                world.current.forEach(function (coordinates) {
                    markCell.aliveAt(coordinates);
                });
                tick();
            };

        window.onload = function () {
            initialize();
            setInterval(render, TIME_INTERVAL);
        };
    };

    Game({
        selectors: {
            world: 'world'
        },
        urls: {
            display: '/world',
            tick: '/world/tick'
        }
    });
}());
(function () {
    var MarkCell = function (options) {
            var height = options.height,
                width = options.width,
                context = options.context,

                SIZE = 4,

                aliveAt = function (cell) {
                    var colour = "rgb(" + (100 + cell.generation) + ", 90, 100)";
                    drawAtWithColour(cell, colour);
                },

                deadAt = function (cell) {
                    var colour = "rgb(200, 255, 200)";
                    drawAtWithColour(cell, colour);
                },

                drawAtWithColour = function (cell, colour) {
                    var x = cell.x,
                        y = cell.y,
                        generation = cell.generation;
                        x1 = x * SIZE + width / 2 + SIZE / 2,
                        y1 = y * SIZE + height / 2 + SIZE / 2;

                    context.fillStyle = colour;
                    context.fillRect(x1, y1, SIZE - 1, SIZE - 1);
                };

            return {
                aliveAt: aliveAt,
                deadAt: deadAt
            };
    };

    var Game = function (window, document, options) {
        var WIDTH = 1280,
            HEIGHT = 800,
            TIME_INTERVAL = 1000,
            window = window,
            document = document,
            selectors = options.selectors,
            urls = options.urls,
            displayUrl = urls.display,
            tickUrl = urls.tick,
            markCell,

            initialize = function (options) {
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
                world.previous.forEach(function (cell) {
                    markCell.deadAt(cell);
                });
                world.current.forEach(function (cell) {
                    markCell.aliveAt(cell);
                });
                tick();
            };

        window.onload = function () {
            initialize();
            window.setInterval(render, TIME_INTERVAL);
        };
    };

    var options = {
        selectors: {
            world: 'world'
        },
        urls: {
            display: '/world',
            tick: '/world/tick'
        }
    };

    Game(window, document, options);
} ());
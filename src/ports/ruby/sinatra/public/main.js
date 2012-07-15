(function () {
    var MarkCell = function (options) {
            var height = options.height,
                width = options.width,
                context = options.context,

                SIZE = 4,
                ALIVE_COLOUR = "#cc3366",
                DEAD_COLOUR = "#acc8ac",

                markAlive = function (coordinates) {
                    drawAt(coordinates, ALIVE_COLOUR);
                },

                markDead = function (coordinates) {
                    drawAt(coordinates, DEAD_COLOUR);
                },

                drawAt = function (coordinates, colour) {
                    var x = coordinates[0],
                        y = coordinates[1],
                        x1 = x * SIZE + width / 2 + SIZE / 2,
                        y1 = y * SIZE + height / 2 + SIZE / 2;

                    context.fillStyle = colour;
                    context.fillRect(x1, y1, SIZE - 1, SIZE - 1);
                };

            return {
                aliveAt: markAlive,
                deadAt: markDead
            };
    };

    var World = function (options) {
        var selectors = options.selectors,
            urls = options.urls,
            displayUrl = urls.display,
            tickUrl = urls.tick,
            markCell = undefined,

            initialize = function () {
                var canvas = document.getElementById(selectors.world)
                    context = canvas.getContext('2d');
                markCell = new MarkCell({
                    context: context,
                    width: 300,
                    height: 300
                });
            },

            currentWorld = function () {
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
                currentWorld().forEach(function (coordinates) {
                    markCell.aliveAt(coordinates);
                });
            };

        window.onload = function () {
            initialize();
            render();
        };
    };

    var world = new World({
        selectors: {
            world: 'world'
        },
        urls: {
            display: '/world',
            tick: '/world/tick'
        }
    });
}());
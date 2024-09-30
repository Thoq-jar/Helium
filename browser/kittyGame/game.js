"use strict";
$(() => {
    let score = 0;
    let isJumping = false;
    let obstacleSpeed = 5;
    let gameOver = false;
    const $obstacle = $('.obstacle');
    const $cat = $('.cat');
    const $score = $('#score');
    const $gameOver = $('.game-over');
    const $finalScore = $('#final-score');
    function startGame() {
        gameOver = false;
        $obstacle === null || $obstacle === void 0 ? void 0 : $obstacle.css('right', '-40px');
        score = 0;
        obstacleSpeed = 10;
        $score === null || $score === void 0 ? void 0 : $score.text(score.toString());
        $gameOver === null || $gameOver === void 0 ? void 0 : $gameOver.hide();
        gameLoop();
    }
    function gameLoop() {
        if (!gameOver) {
            moveObstacle();
            requestAnimationFrame(gameLoop);
        }
    }
    function moveObstacle() {
        var _a;
        const obstaclePositionStr = $obstacle === null || $obstacle === void 0 ? void 0 : $obstacle.css('right');
        const obstaclePosition = obstaclePositionStr ? parseInt(obstaclePositionStr, 10) : 0;
        const windowWidth = (_a = $(window)) === null || _a === void 0 ? void 0 : _a.width();
        if (windowWidth && obstaclePosition > windowWidth) {
            $obstacle === null || $obstacle === void 0 ? void 0 : $obstacle.css('right', '-40px');
            score++;
            $score === null || $score === void 0 ? void 0 : $score.text(score.toString());
            increaseDifficulty();
        }
        else
            $obstacle === null || $obstacle === void 0 ? void 0 : $obstacle.css('right', `${obstaclePosition + obstacleSpeed}px`);
        if (collision())
            endGame();
    }
    function increaseDifficulty() {
        if (score % 10 === 0 && score !== 0)
            obstacleSpeed -= 5;
        else
            obstacleSpeed += 1;
    }
    function collision() {
        const catOffset = $cat === null || $cat === void 0 ? void 0 : $cat.offset();
        const obstacleOffset = $obstacle === null || $obstacle === void 0 ? void 0 : $obstacle.offset();
        if (!catOffset || !obstacleOffset)
            return false;
        const catBottom = catOffset.top + (($cat === null || $cat === void 0 ? void 0 : $cat.height()) || 0);
        const catLeft = catOffset.left;
        const catRight = catLeft + (($cat === null || $cat === void 0 ? void 0 : $cat.width()) || 0);
        const obstacleTop = obstacleOffset.top;
        const obstacleLeft = obstacleOffset.left;
        const obstacleRight = obstacleLeft + (($obstacle === null || $obstacle === void 0 ? void 0 : $obstacle.width()) || 0);
        return (catBottom >= obstacleTop && catLeft < obstacleRight && catRight > obstacleLeft);
    }
    function simulatePhysics(mode) {
        if (mode === "Jump") {
            if (!isJumping && !gameOver) {
                isJumping = true;
                $cat === null || $cat === void 0 ? void 0 : $cat.animate({ bottom: '+=350px' }, 450, () => $cat === null || $cat === void 0 ? void 0 : $cat.animate({ bottom: '-=350px' }, 400, () => isJumping = false));
            }
            else if (gameOver)
                startGame();
        }
    }
    function endGame() {
        gameOver = true;
        isJumping = false;
        $finalScore === null || $finalScore === void 0 ? void 0 : $finalScore.text(score.toString());
        $gameOver === null || $gameOver === void 0 ? void 0 : $gameOver.show();
    }
    $(document).on('keydown', (event) => {
        if (event.key === ' ')
            simulatePhysics("Jump");
    });
    $(document).on('click', () => simulatePhysics("Jump"));
    startGame();
});
//# sourceMappingURL=game.js.map
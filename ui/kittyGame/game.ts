$((): void => {
  let score: number = 0;
  let isJumping: boolean = false;
  let obstacleSpeed: number = 5;
  let gameOver: boolean = false;

  const $obstacle = $('.obstacle');
  const $cat = $('.cat');
  const $score = $('#score');
  const $gameOver = $('.game-over');
  const $finalScore = $('#final-score');

  function startGame(): void {
    gameOver = false;
    $obstacle?.css('right', '-40px');
    score = 0;
    obstacleSpeed = 10;
    $score?.text(score.toString());
    $gameOver?.hide();
    gameLoop();
  }

  function gameLoop(): void {
    if (!gameOver) {
      moveObstacle();
      requestAnimationFrame(gameLoop);
    }
  }

  function moveObstacle(): void {
    const obstaclePositionStr = $obstacle?.css('right');
    const obstaclePosition: number = obstaclePositionStr ? parseInt(obstaclePositionStr, 10) : 0;

    const windowWidth = $(window)?.width();
    if (windowWidth && obstaclePosition > windowWidth) {
      $obstacle?.css('right', '-40px');
      score++;
      $score?.text(score.toString());
      increaseDifficulty();
    } else $obstacle?.css('right', `${obstaclePosition + obstacleSpeed}px`);

    if (collision()) endGame();
  }

  function increaseDifficulty(): void {
    if (score % 10 === 0 && score !== 0) obstacleSpeed -= 5;
    else obstacleSpeed += 1;
  }

  function collision(): boolean {
    const catOffset = $cat?.offset();
    const obstacleOffset = $obstacle?.offset();

    if (!catOffset || !obstacleOffset) return false;

    const catBottom: number = catOffset.top + ($cat?.height() || 0);
    const catLeft: number = catOffset.left;
    const catRight: number = catLeft + ($cat?.width() || 0);

    const obstacleTop: number = obstacleOffset.top;
    const obstacleLeft: number = obstacleOffset.left;
    const obstacleRight: number = obstacleLeft + ($obstacle?.width() || 0);

    return (catBottom >= obstacleTop && catLeft < obstacleRight && catRight > obstacleLeft);
  }

  function simulatePhysics(mode: string): void {
    if (mode === "Jump") {
      if (!isJumping && !gameOver) {
        isJumping = true;
        $cat?.animate({bottom: '+=350px'}, 450, () => $cat?.animate({bottom: '-=350px'}, 400, () => isJumping = false));
      } else if (gameOver) startGame();
    }
  }

  function endGame(): void {
    gameOver = true;
    isJumping = false;
    $finalScore?.text(score.toString());
    $gameOver?.show();
  }

  $(document).on('keydown', (event) => {
    if (event.key === ' ') simulatePhysics("Jump");
  });

  $(document).on('click', () => simulatePhysics("Jump"));

  startGame();
});
var canvasDiv = document.getElementById('p5-canvas');
var canvasDivWidth = canvasDiv.offsetWidth;
var buttonsDiv = document.getElementsByClassName('button-container')[0];
var retakeButtonDiv = document.getElementsByClassName('button-retake')[0];
var shareButtonDiv = document.getElementsByClassName('button-share')[0];

var capture, bCapture, captureImage;
var cornerAura, brightnessMask, resultAura;

function preload() {
  cornerAura = loadImage("images/aura-corner.png");
  canvasDiv.onclick = takePicture;
}

function setup() {
  var cnv = createCanvas(canvasDivWidth, canvasDivWidth);
  cnv.parent('p5-canvas');

  capture = createCapture(VIDEO);
  capture.size(960, 720);
  capture.hide();
  bCapture = true;

  captureImage = createImage(capture.width, capture.height);
  brightnessMask = createGraphics(width, height);
  brightnessMask.pixelDensity(1);
  resultAura = createGraphics(width, height);
  resultAura.pixelDensity(1);

  imageMode(CENTER);
}

function draw() {
  background(0);
  if(bCapture) {
    captureImage.copy(capture,
                       0, 0, capture.width, capture.height,
                       0, 0, captureImage.width, captureImage.height);
    adjustBrightnessContrast(captureImage, 255);
    image(captureImage, width/2, height/2);
  } else {
    image(resultAura, width/2, height/2, width, height);
  }
}

function drawAuras(bground) {
  resultAura.imageMode(CENTER);

  resultAura.push();
  resultAura.translate(resultAura.width/2, resultAura.height/2);

  resultAura.noTint();
  resultAura.image(bground, 0, 0);


  for (var i=0; i<8; i++) {
    if (random(1.0) > 0.4) {
      resultAura.push();
      resultAura.rotate(TWO_PI * i / 8.0 + random(1.0) * PI/8.0);

      if (random(1) < 0.333) {
        resultAura.tint(0, 0, 150, 200);
      } else if (random(1) < 0.66) {
        resultAura.tint(0, 150, 0, 200);
      } else {
        resultAura.tint(150, 0, 0, 200);
      }

      resultAura.translate(-resultAura.width/random(2, 8),
                           -resultAura.height/random(2, 8));
      resultAura.image(cornerAura, 0, 0, resultAura.width, resultAura.height);

      resultAura.tint(255, 200);
      resultAura.image(cornerAura, -resultAura.width/10, -resultAura.height/10,
                       resultAura.width, resultAura.height);
      resultAura.pop();
    }
  }
  resultAura.pop();
}

function takePicture() {
  bCapture = false;
  canvasDiv.onclick = function(){};

  drawAuras(captureImage);
  buttonsDiv.style.display = "flex";

  retakeButtonDiv.onclick = function() {
    bCapture = true;
    buttonsDiv.style.display = "none";
    canvasDiv.onclick = takePicture;
  }

  shareButtonDiv.onclick = function() {
    resizeCanvas(canvasDivWidth/3, canvasDivWidth/3);
    buttonsDiv.style.display = "none";
  }
}

function adjustBrightnessContrast(pimg, value) {
  var original = createImage(pimg.width, pimg.height);
  original.copy(pimg,
                0, 0, pimg.width, pimg.height,
                0, 0, original.width, original.height);

  brightnessMask.background(value);

  pimg.blend(brightnessMask,
    0, 0, brightnessMask.width, brightnessMask.height,
    0, 0, pimg.width, pimg.height, DARKEST);

  pimg.blend(original,
    0, 0, original.width, original.height,
    0, 0, pimg.width, pimg.height, BURN);
}

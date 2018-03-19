import processing.video.*;

Capture cam;
PGraphics brightnessMask;
PImage photo, cornerAura;

boolean bCapture;

void setup() {
  size(720, 720);
  photo = loadImage("tgh.jpg");
  photo.resize(0, height);

  cornerAura = loadImage("aura-corner.png");
  brightnessMask = createGraphics(width, height);

  bCapture = true;
  cam = new Capture(this, 1280, 720, "FaceTime HD Camera", 30);
  cam.start();

  imageMode(CENTER);
}

void draw() {
  if (cam.available()) {
    cam.read();
    cam.resize(0, height);
    adjustBrightnessContrast(cam, 255);
  }

  if (bCapture) {
    image(cam, width/2, height/2);
  }
}

void drawAuras() {
  drawAuras(photo);
}

void drawAuras(PImage bground) {
  pushMatrix();
  translate(width/2, height/2);

  noTint();
  image(bground, 0, 0);

  for (int i=0; i<8; i++) {
    if (random(1.0) > 0.4) {
      pushMatrix();
      rotate(TWO_PI * i / 8.0 + random(1.0) * PI/8.0);

      if (random(1) < 0.333) {
        tint(0, 0, 150, 200);
      } else if (random(1) < 0.66) {
        tint(0, 150, 0, 200);
      } else {
        tint(150, 0, 0, 200);
      }

      translate(-width/random(2, 8), -height/random(2, 8));
      image(cornerAura, 0, 0, width, height);

      tint(255, 200);
      image(cornerAura, -width/10, -height/10, width, height);
      popMatrix();
    }
  }
  popMatrix();
}

void mousePressed() {
  if (bCapture) {
    drawAuras(cam);
  }
  bCapture = !bCapture;
}

void adjustBrightnessContrast(PImage pimg, int value) {
  PImage original = createImage(pimg.width, pimg.height, ARGB);
  original.set(0, 0, pimg);

  brightnessMask.beginDraw();
  brightnessMask.background(value);
  brightnessMask.endDraw();

  pimg.blend(brightnessMask,
    0, 0, brightnessMask.width, brightnessMask.height,
    0, 0, pimg.width, pimg.height, DARKEST);

  pimg.blend(original,
    0, 0, original.width, original.height,
    0, 0, pimg.width, pimg.height, BURN);
}
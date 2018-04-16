import processing.video.*;

Capture cam;
PGraphics dodgeMask, burnMask;
PImage photo, cornerAura;

boolean bCapture;

void setup() {
  size(720, 720);
  photo = loadImage("tgh.jpg");
  photo.resize(0, height);

  cornerAura = loadImage("aura-corner.png");
  dodgeMask = createGraphics(width, height);
  burnMask = createGraphics(width, height);

  bCapture = true;
  cam = new Capture(this, 1280, 720, "FaceTime HD Camera", 30);
  cam.start();

  imageMode(CENTER);
}

void draw() {
  if (cam.available()) {
    cam.read();
    cam.resize(0, height);
    adjustBrightnessContrast(cam);
  }

  if (bCapture) {
    tint(255);
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

  int numQuestions = 4;
  for (int i = 0; i < numQuestions; i++) {
    pushMatrix();
    rotate(TWO_PI * i / numQuestions + random(1.0) * PI/numQuestions);

    color c = ((random(1) < 0.333) ? color(150, 0, 0, 150) :
      ((random(1) < 0.333) ? color(0, 150, 0, 150) :
      color(0, 0, 150, 150)));

    tint(c);
    translate(-width/random(2, 8), -height/random(2, 8));
    image(cornerAura, 0, 0, width, height);
    cornerAura.resize((int)(0.25 * cornerAura.width), 0);

    tint((c & 0xffffff) | (0xc8 << 24));
    image(cornerAura, -width/10, -height/10, width, height);
    cornerAura.resize((int)(4 * cornerAura.width), 0);

    popMatrix();
  }
  popMatrix();
}

void mousePressed() {
  if (bCapture) {
    drawAuras(cam);
  }
  bCapture = !bCapture;
}

void adjustBrightnessContrast(PImage img) {
  dodgeMask.beginDraw();
  dodgeMask.background(18);
  dodgeMask.endDraw();

  burnMask.beginDraw();
  burnMask.background(180);
  burnMask.endDraw();

  img.blend(dodgeMask,
    0, 0, dodgeMask.width, dodgeMask.height,
    0, 0, img.width, img.height, DODGE);

  img.blend(burnMask,
    0, 0, burnMask.width, burnMask.height,
    0, 0, img.width, img.height, BURN);
}
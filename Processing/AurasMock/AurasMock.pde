import processing.video.*;

Capture cam;
PGraphics brightnessMask;
PImage photo, acrossAura, offCenterAura;
ArrayList<PImage> cornerAuras;

boolean bCapture;

void setup() {
  size(720, 720);
  photo = loadImage("tgh.jpg");
  photo.resize(0, height);

  brightnessMask = createGraphics(width, height);

  acrossAura = loadImage("aura-across.png");
  offCenterAura = loadImage("aura-offcenter.png");
  cornerAuras = new ArrayList<PImage>();

  for (int i=0; i<8; i++) {
    cornerAuras.add(loadImage("aura-corner.png"));
  }

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

  for (int i=0; i<cornerAuras.size(); i++) {
    if (random(1.0) > 0.4) {
      pushMatrix();
      rotate(TWO_PI * i / cornerAuras.size() + random(1.0) * PI/8.0);

      if (random(1) < 0.333) {
        tint(0, 0, 150, 200);
      } else if (random(1) < 0.66) {
        tint(0, 150, 0, 200);
      } else {
        tint(150, 0, 0, 200);
      }

      translate(-width/random(2, 8), -height/random(2, 8));
      image(cornerAuras.get(i), 0, 0, width, height);

      tint(255, 200);
      image(cornerAuras.get(i), -width/10, -height/10, width, height);
      popMatrix();
    }
  }

  if (random(1.0) > 1.5) {
    pushMatrix();
    translate(0, -height/4.0);
    rotate(random(0, TWO_PI));

    tint(0, 0, 150, 200);
    image(acrossAura, 0, 0, 1.5*width, 1.5*height);

    tint(255, 128);
    image(acrossAura, 0, 0, 1.5*width, height/2.0);
    popMatrix();
  } else if (random(1.0) > 1.5) {
    pushMatrix();
    translate(-width/4.0, height/8.0);
    rotate(random(-PI/8.0, 0));

    tint(0, 0, 150, 200);
    image(offCenterAura, 0, 0, 1.5*width, 1.5*height);

    tint(255, 128);
    image(offCenterAura, 0, 0, width/1.5, height/1.5);
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

void keyPressed() {
  mousePressed();
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
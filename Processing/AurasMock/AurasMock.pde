PImage photo, acrossAura, offCenterAura;
ArrayList<PImage> cornerAuras;

void setup() {
  size(720, 720);
  photo = loadImage("tgh.jpg");
  acrossAura = loadImage("aura-across.png");
  offCenterAura = loadImage("aura-offcenter.png");
  cornerAuras = new ArrayList<PImage>();

  for (int i=0; i<8; i++) {
    cornerAuras.add(loadImage("aura-corner.png"));
  }
  imageMode(CENTER);
  drawAuras();
}

void draw() {
  if ((millis() / 1000) % 3 == 0) {
    drawAuras();
  }
}

void drawAuras() {
  pushMatrix();
  translate(width/2, height/2);

  noTint();
  image(photo, 0, 0, width, height);

  for (int i=0; i<cornerAuras.size(); i++) {
    if (random(1.0) > 0.4) {
      pushMatrix();
      rotate(TWO_PI * i / cornerAuras.size() + random(1.0) * PI/8.0);

      if (random(1) < 0.333) {
        tint(0, 0, 150, 220);
      } else if (random(1) < 0.66) {
        tint(0, 150, 0, 220);
      } else {
        tint(150, 0, 0, 220);
      }

      translate(width/17.0, height/17.0);
      image(cornerAuras.get(i), 0, 0, width*1.5, height*1.5);

      tint(255);
      image(cornerAuras.get(i), -width/7.0, -height/7.0, width*1.5, height*1.5);
      popMatrix();
    }
  }

  if (random(1.0) > 0.5) {
    pushMatrix();
    rotate(random(-PI/8.0, PI/8.0));
    tint(random(0), random(0), random(150, 150), 220);
    image(acrossAura, 0, 0, width*1.5, height*1.5);

    tint(255, 220);
    image(acrossAura, 0, -height/7.0, width*1.5, height*1.5);
    popMatrix();
  } else if (random(1.0) > 0.5) {
    pushMatrix();
    rotate(random(-PI/8.0, 0));
    tint(random(0), random(0), random(150, 150), 128);
    image(offCenterAura, width/7.0, 0, width*1, height*1);

    tint(255, 64);
    image(offCenterAura, width/7.0, 0, width*1, height*1);
    popMatrix();
  }

  popMatrix();
}

void mousePressed() {
  drawAuras();
}
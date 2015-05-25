// Other functions

void keyPressed()
{
  if (key == ' ')
  {
    interactive=!interactive; // switch between automated and interactive modes
  }
}

void drawInteraction()
{
  if (interactive)
  {
    P = mouseX;
  } else
  {
    P = frameCount*dimStep*2%width;
    fill(255, 0, 50);
    noStroke();
    // ellipse(P, height/2, 5, 5);
  }
}


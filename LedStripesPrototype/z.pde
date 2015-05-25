// Other functions

void keyPressed()
{
  if (key == ' ')
  {
    interactive=!interactive; // switch between automated and interactive modes 
    // TODO: add 3 automated modes (1. random pulsating (idle mode), 2. intro, 3. flow mode)
  }
}

void updatePoint()
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


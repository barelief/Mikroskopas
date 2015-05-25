// this class animates the color of the Stripe
// depending on given function color can animate 
// FORWARD (ie from 0 to 255)
// BACK (ie from 255 to 0)
// PAUSE (dont animate at all)

class VerticalStripe 
{
  Mode mode=Mode.PAUSE; 
  boolean isLocked=false; // is animation locked
  int dimColor=0; // led dimming color from 0 to 255
  int id; // stripe ID, for rendering and control purposes
  int x; // X position of the stripe

    VerticalStripe(int id) // init
  {
    this.id=id; 
    x=id*stripeWidth + gap*id; 
    isLocked=false;
  }

  void draw()
  {
    render();
    update();
    //println("drawing");
  }

  void render()
  {
    fill(0);
    // rect(x, 0, stripeWidth, stripeHeight);
    // ellipseMode(CORNER);
    //fill(dimColor, dimColor, 0);
    pushStyle();
    imageMode(CENTER);
    tint(255, constrain(dimColor, 0, 255));
    // tint(constrain(dimColor,0,255));

    int ellipseAmount = 9;
    int ellipseRadius = stripeHeight / ellipseAmount;
    for (int i=0; i<ellipseAmount; i++)
    {
      // ellipse(x+stripeWidth/2,i*ellipseRadius + stripeWidth/2,stripeWidth/2,stripeWidth/2); 
      image(led, x+stripeWidth/2, i*ellipseRadius + stripeWidth/2, stripeWidth*.6, stripeWidth*.6);
    }

    popStyle();
    showDebugInfo();
  }

  private void showDebugInfo() 
  {
    // fill(255, 0, 50);
    fill(255);
    textAlign(CENTER, CENTER);
    text(dimColor, x + stripeWidth/2, stripeHeight-20);
  }

  void update()
  {

    if (dimColor<0 || dimColor>255)
    {
      mode=Mode.PAUSE;
      println("Mode: PAUSED");
      isLocked=false;
    }

    dimColor=constrain(dimColor, 0, 255); // do not exceed allowed values
    
    switch(mode)
    {
    case PAUSE:
      // do not update color value;
      if (dimColor < 0 ) dimColor=0;
      break;
    case FORWARD:
      dimColor+=dimStep;
      break;
    case BACK:
      dimColor-=dimStep;
      break;
    }
  }

  void setMode(Mode m)
  {
    mode = m;
    println("Mode: "+mode);
  }

  void waitForInput(int input)
  {
    // if mouse is Over the stripe
    if (!isLocked)
    {
      if ( abs(input-(x+stripeWidth/2) ) < stripeWidth/2 )
      {
        setMode(Mode.FORWARD);
        isLocked=true;
      } else 
      {
        setMode(Mode.BACK);
        isLocked=true;
      }
    }
  }
}


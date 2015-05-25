void draw()
{
  image(bg,0,0);
  for (int i=0; i<stripeAmount; i++)
  {
    stripe[i].draw();
    stripe[i].waitForInput(P);
  }
  drawInteraction();
}

void setup()
{
  size(stripeAmount*stripeWidth + gap*stripeAmount, stripeHeight); // screensize
  for (int i=0; i<stripeAmount; i++) // 
  {
    stripe[i]=new VerticalStripe(i); // construct stripe objects
  }
   
  bg = loadImage("grass.jpg"); // load background image http://i.imgur.com/Tl5PGYM.jpg
  led = loadImage("sun.png"); // load led image http://i.imgur.com/N0n7rbM.png
}


int stripeAmount = 16; 
VerticalStripe[] stripe=new VerticalStripe[stripeAmount]; // create array of stripees
int stripeWidth = 40;
int stripeHeight = 600; 
int dimStep = 5; // how fast is color dimming
int gap = 50; // gap between stripes

int P; // stripe animation control point
boolean interactive = false; // is animation interactive or not

PImage bg, led; // image obejcts for better visuals (http://imgur.com/Tl5PGYM,N0n7rbM)

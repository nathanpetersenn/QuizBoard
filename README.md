#QuizBoard

All files relating to the 2012-2013 Quiz Board built by Nathan Petersen and Isaac Kasten for Honors Physics live here.

These include:
 - HTML5 app for making more question cards
 - Reports about the quiz board
 - Arduino code for quiz board
 - Scanned plans for quiz board

##I didn't think Quiz Boards were that complicated...?

You are correct. *Normal* quiz boards are not complicated at all; a couple lights, some wire, a battery, and a magic wand is all you need! But this quiz board is different.

##How it works
This Quiz Board contains some basic components to interact with the user:
 - Green LEDs
 - Red LEDs
 - Speaker
 - 5 push buttons
 - Slot for question cards

Under the hood though, the Quiz Board contains an Arduino micro-controller. This is like a computer, and it serves as the brains of the operation. Every question card has holds in the bottom of it that are feed into the slot. Once in the slot, the Arduino reads the answer (encoded in the holes) and waits for the user to press a button. Each button corresponds to an answer on the card. If a correct answer is selected, the green LEDs light up and a happy sound is played. For wrong answers, the red LEDs are illuminated and a sad sound is played. Basic operation is very simple and allows for a **infinite** number of questions (on seperate cards).

###Easter eggs
Within the code for the Arudino, there are a couple of [easter eggs](http://goo.gl/bLm1HF) to play with.
####All buttons
This plays random beeps like classic computers would. Pressing middle three buttons returns to "main menu".
####All buttons minus middle button
This turns buttons into a keyboard. Pressing a button will play a tone and light the LEDs. Sliding a credit card in slot will change the octave. Pressing middle three buttons returns to "main menu".
####Outside two buttons
This creates a tone bender. Press the middle button to play tone. While playing tone, press the other buttons to bend pitch. Pressing middle three buttons returns to "main menu".


##Printing Custom Questions
Custom cards can be printed and cut out for quiz board reading. Follow the steps below for best results.

>Note: using cardstock paper results in better cards that are less prone to error!

1. Open `questionPrinter.html` in ~~Chrome~~ your favorite browser.
2. Add the question information in the form that presents itself.
 - Note: the final card will have a similar layout to the form.
3. After adding all your information and selecting the correct answer, hit the "Print Question Card" button.
4. The finished question card will now appear on the screen.
5. Print the finished question card by pressing [Ctrl]-[P]
 - Rotate page to "Portrait" orientation.
 - Make sure to select "Background colors and images" for printing!
6. Cut out around the black edges
7. Cut out the shaded circles.

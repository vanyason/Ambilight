import javax.imageio.ImageIO;
import javax.management.monitor.Monitor;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

import arduino.Arduino;

public class PC_Controller {
   /* static void increaseLight() {
        int favourite;
        int gap;
        if (r > g && r > b)
            favourite = r;
        else if (g > r && g > b)
            favourite = g;
        else
            favourite = b;
        gap = 255 - favourite;
        r += gap;
        g += gap;
        b += gap;

    }*/

    public static void main(String[] args) throws InterruptedException {

        //  Handles OS signals (the correct completion of the program )
        Runtime.getRuntime().addShutdownHook(new Thread() {
            @Override
            public void run() {
                System.out.println("Finished");
            }
        });

        String portName = "";
        int offset = 0;
        int width = 0;
        int height = 0;
        Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
        BufferedImage screenShot = null;
        Robot robot = null;
        int r = 0, g = 0, b = 0;

        // Parse CMD
        try {
            if (args.length == 0) {
                System.out.println("Pass serial port name");
                System.exit(0);
            } else if (args.length == 1) {
                portName = args[0];
                offset = 0;
                width = screenSize.width;
                height = screenSize.height;
            } else if (args.length == 4) {
                portName = args[0];
                offset = Integer.parseInt(args[1]);
                width = Integer.parseInt(args[2]);
                height = Integer.parseInt(args[3]);
            } else
                throw new IllegalArgumentException();
        } catch (Exception e) {
            System.out.println("Wrong arguments");
            System.exit(0);
        }

        //  Shrink region
        int offsetY = 350;
        int offsetX = offset + offsetY;
        int newWidth = width - 2 * offsetY;
        int newHeight = height - 2 * offsetY;


        //  Create Robot to take screenshots
        try {
            robot = new Robot();
            File outputfile = new File("saved.png");

            ImageIO.write(robot.createScreenCapture(new Rectangle(offsetX, offsetY, newWidth, newHeight)), "png", outputfile);
        } catch (Exception e) {
            System.out.println("Something wrong with getting screenshot");
            System.exit(1);
        }


        try {
            Arduino arduino = new Arduino(portName, 9600);
            boolean connected = arduino.openConnection();
            Thread.sleep(2000);

            while (connected) {
                screenShot = robot.createScreenCapture(new Rectangle(offsetX, offsetY, newWidth, newHeight));

                int pixel;
                r = 0;
                g = 0;
                b = 0;

                //  Skipping neighboring pixels to speedup loop;
                for (int i = 0; i < newWidth; i += 2) {
                    for (int j = 0; j < newHeight; j += 2) {
                        pixel = screenShot.getRGB(i, j);
                        r += (int) (255 & pixel >> 16);
                        g += (int) (255 & pixel >> 8);
                        b += (int) (255 & pixel);
                    }
                }

                //  getAverage
                r /= (height * width / 4);
                g /= (height * width / 4);
                b /= (height * width / 4);



                //  increase brightness
                int favourite;
                double gap;
                if (r >= g && r >= b)
                    favourite = r;
                else if (g >= r && g >= b)
                    favourite = g;
                else
                    favourite = b;
                gap = 255. / (double) favourite ;
                r *= gap;
                g *= gap;
                b *= gap;

                //  Correct white/black to orange
                if((r + g + b)/3 > 240 || (r + g + b)/3 < 40)
                {
                    r = 255;
                    g = 230;
                    b = 30;
                }





                arduino.serialWrite('!' + " " + Integer.toString(r) + " " + Integer.toString(g) + " " + Integer.toString(b));
                //arduino.serialWrite('!' + " " + Integer.toString(0) + " " + Integer.toString(255) + " " + Integer.toString(255));

                System.out.println(r + " " + g + " " + b + " ");
                Thread.sleep(100);   //  for safety


            }
        } catch (Exception e) {
            System.out.println("Something wrong at sending data to arduino");
            System.exit(1);


        }
    }
}
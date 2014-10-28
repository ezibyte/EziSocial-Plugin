**Using EziSocial v2.4 with Cocos2dx v3.x**

- - -

 1. Generate Cocos2d-x project using cocos script
 2. Go to your Cocos2dx project directory.
 3. Copy ezibyte folder github and paste it your project directory.

> For example: project directory is TestProject, then ezibyte folder needs to be copied to TestProject directory. i.e. TestProject/ezibyte

Suppose you have downloaded EziSocial version 2.3 at /home/ezisocial_2.3

Example:

    $ cd cocos2d-x
    $ ./setup.py
    $ source FILE_TO_SAVE_SYSTEM_VARIABLE
    $ cocos new MyGame -p com.your_company.mygame -l cpp -d /home
    $ cd /home/MyGame
    $ cp /home/ezisocial_2.3/Cocos2dx_3.x/ezibyte /home/MyGame 

After that follow the tutorial from here:

  - [Adding EziSocial to existing iOS Cocos2dx v3.x project.](http://ezibyte.com/how-to-add-ezisocial-to-existing-ios-game/)
  - [Adding EziSocial to existing Android Cocos2dx v3.x project.](http://ezibyte.com/cocos2d-x-v3-x-how-to-add-ezisocial-to-existing-android-game/)
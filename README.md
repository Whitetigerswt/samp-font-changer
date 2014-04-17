samp-font
=========

Change the ingame font (and more) of the SA-MP chat, dialogs, and 3D text labels without complicated hex editing!

Early adopters
----------
If you're reading this now, you're one of the first to check this site. I've uploaded a version in the RELEASE section of github on this repo. give it a download a try it before I go public. Test some things, iron it out. You can report things to me all day. I'm on the SA-MP IRC all day. http://wiki.sa-mp.com/wiki/IRC. my username is Whitetiger or Whitetiger_PC, you can nick alert me or PM if you want to tell me something

Requirements to run:
----------

- VC++ 2010 redistributable

Picking a font
----------

Not every font makes a good alternative, some fonts do not support color embedding in dialogs (though, all seem to work when used in the chat). so when picking a font for dialogs and 3D text labels, take this into consideration if you rejoin a server and start seeing a bunch of {FFFFFF} codes. An example of one that doesn't support it is "Bradley Hand ITC", an example of one that does support it is "David"

How to use
----------
so you've made a mod to change the font in the chat, how do you use it? Well, the first time you run your game with this mod loaded it will generate the default .cfg. these are the values that SA-MP uses by default when the game runs. You can tweak these things and just make the chat a little but smaller if you'd like, or you can change the font completely and overhaul the chat. There are seperate settings for dialogs. you can change the way dialogs appear on your screen too.

When the config is generated ("sampfont.cfg" in the GTA directory you installed this mod) it should appear something like this:

![ScreenShot](https://sixtytiger.com/tiger/random/default_cfg.png)

wow! this seems overwhelming doesn't it? well, the parameters are explained by D3DXCreateFont. this mod is just a wrapper for that function in SA-MP.dll almost. so, you can get an explanation of all the parameters for that here: http://msdn.microsoft.com/en-us/library/windows/desktop/bb172773(v=vs.85).aspx

The first thing i'm going to do is change the font to something else. you don't have to, but I'll do that for an example. So, to find a new font to use navigate to Fonts in control panel.

![ScreenShot](https://sixtytiger.com/tiger/random/fontslist.png)

here we have a list of installed fonts, in GROUP form! you need to get the individual font. so I looked around a bit and i decided on a font, called French Script MT Regular, double click on it and check the WINDOW TITLE, this is the name you need to copy (NOT WHAT SHOWS IN THE INSTALLED FONTS WINDOW!)

![ScreenShot](https://sixtytiger.com/tiger/random/myfont.png)

now, in the installed fonts window, this font is called French Script MT Regular. If you had copied that into the config file, it wouldn't have worked. The real name of this font is French Script MT (As you can see by the window title on it).

so copy this font name into the Font key under [Chat] and [ChatShadow]. a quick side note, for the best appeal, Chat and ChatShadow should have IDENTICAL settings, you should really never make them different unless you know what you're doing. the same applies to 3DText and 3DTextShadow.

Now launch the game.

![ScreenShot](https://sixtytiger.com/tiger/random/low_height_width.png)

Wow, this is difficult to read isn't it?

lets change the height and width on the settings so its easier to read.

so change the height to 25, and the width to 25, on both [Chat] and [ChatShadow].

![ScreenShot](https://sixtytiger.com/tiger/random/high_height_width.png)

whoa, thats a bit to high. now you can mess around with the values if you want, but I found the best value for my 1920x1080 resolution to be 10 width, 22 height.

![ScreenShot](https://sixtytiger.com/tiger/random/perfect_height_width.png)

And thats how it's done. You can change the fonts of 3D Text labels, Dialogs, in the same way. or leave the default font, and just change the height and width! You can use any font installed on your PC. I haven't messed around with it a lot yet so I'm not an expert on how pitch, precision, miplevels, actually affect the look of it, but I really look forward to the configs the community can output!!

Samples
----------
![ScreenShot](https://www.sixtytiger.com/tiger/random/dialog_font.png)

This is a font called "Brush Script MT Italic". when picking a dialog font and size, it's important to note that it may break the pretty indentions servers have finely tuned to the Arial font.

![ScreenShot](https://www.sixtytiger.com/tiger/random/shrink_chat_size.png)

This is the default settings, same Arial font, but the chat size is shrunken a little bit, moving it out of the way of the game, and in my opinion making it easier to read.



WaterWM
An improved version of my previous window manager, TiredWM. You previously could configure TiredWM only via hooks.
WaterWM changes that: it has his own config.h file!! WaterWM is also much less buggy than TiredWM.
WaterWM has also arguments, such as:
  - nointro -> does not show intros
  - nonotes -> does not show notes, future
  - nodebug -> does not show debug infos, future
  - silent -> nonotes + nointro + nodebug, future
Another thing TiredWM has never implemented.
WaterWM has also no dependencies other than X, another thing TiredWM misses!
To run it:
  Clone the repo and C.D.:
    git clone https://github.com/imvariety/waterwm.git
    cd waterwm
  Tweak the configuration as you want, then compile it within make
  Wrap it in an X Init Configuration to run it properly:
    echo "xterm && exec $(pwd)/waterwm" > $HOME/.xinitrc
  Then run startx and there you go!!
If you want to install it, in the cloned repo:
    Tweak the config as you want, then compile it within make
    Move it in the /usr/sbin directory:
      mv waterwm /usr/sbin/waterwm
    Create an $HOME/.xinitrc as usual, then you are good to go:
      echo "xterm && exec waterwm" > $HOME/.xinitrc

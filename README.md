# Mac OS X Keycounter

This repository holds code for a simple keypress counter for MacOS. It is not malicious in any way!!! It doesn't even read the keycodes of your presses. Its intended to count the total number of keypresses put into your computer. How you use that information is up to you.

## Usage

Start by cloning the repository and running the proper make commands, shown below. By default, the application installs to `/usr/local/bin/keylogger`, which can easily be changed in the [`Makefile`](https://github.com/caseyscarborough/keylogger/blob/master/Makefile). `make install` may require root access.

```bash
$ git clone https://github.com/caseyscarborough/keylogger && cd keylogger
$ make && make install
```

The application by default logs to `/var/log/keystroke.log`, which may require root access depending on your system's permissions. You can change this in [`keylogger.h`](https://github.com/caseyscarborough/keylogger/blob/master/keylogger.h#L12) if necessary.

```bash
$ keylogger
Logging to: /var/log/keystroke.log
```

If you'd like the application to run on startup, run the `startup` make target:

```bash
$ sudo make startup
```

## Uninstallation

You can completely remove the application from your system (including the startup daemon) by running the following command (logs will not be deleted):

```bash
$ sudo make uninstall
```

## Contributing

Feel free to fork the project and submit a pull request with your changes!

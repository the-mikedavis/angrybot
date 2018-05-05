# AngryBot

_A feisty little 3D printed MeArm._

Tired of helpful robots that make a positive impact in society?
Wondering where Skynet is after all this time?
AngryBot might be right for you.

![Imgur](https://i.imgur.com/6g96LN0.jpg)

AngryBot is a MeArm: a small, dexterous, open source robot design under
development for many years now. While it's usually meant to be laser cut
on a sheet of acrylic, 3D printing is also a viable option. MeArm just
has 4 motors which dictate its movement. With the design, some very smart
people have solved the [inverse kinematics](https://en.wikipedia.org/wiki/Inverse_kinematics),
which is usually a pretty difficult problem for larger robots. The inverse
kinematics allow you to provide the robot with an arbitrary point in 3D
space to reach. The equations can be solved in a way to test if that point
is reachable and further equations can be used to plan the path to bring the
robot there.

AngryBot improves upon the MeArm design by adding a _ping sensor_, which
works similar to bats and submarines (SONAR). As a happy accident, the sensor
itself looks surprisingly like a set of eyes.

## Construction

Most of the assembly follows available instructions from previous MeArm
builders. Here are the different websites I used:

- [Parts (3D Model)](https://www.thingiverse.com/thing:298820/#files)
- [Assembly](http://www.instructables.com/id/MeArm-Build-a-Small-Hackable-Robot-Arm/)
- [Wiring (without a shield)](http://microbotlabs.com/armuno-arduino-schematic.html)
- [Control](https://github.com/phenoptix/me-arm-ik)
- [Configuring](http://bitofahack.com/post/1433701488)
  - for configuring the servos and working with the IK

The construction of the physical arm was based entirely off the instructable.
That being said, 3D printing the model added a series of difficulties that made
construction time painfully long. First, the 3D printer I used couldn't fit the
entire model. To make it work, I cut the model into two halves and printed each
separately. To make the cut, I used MeshLab, finding no other helpful software
for deleting parts of STL files. Then, to prevent pieces flying off the plate
during printing, I built plate adhesion. For these sorts of parts, it meant
that the whole file printed essentially as one big plate, each of the smaller
components connected by thin layers of plastic. To separate the pieces, I used
an exacto-knife. Then, since the parts were printed instead of cut, they were
not the exactly correct size. The printing process left some of the holes just
a bit too small, which was the hardest part. Some of the servo holders took
up to a half hour to drill out each to fit in the part. The chassis of the
robot has parts that fit closely together to make a stable cage. To make these
right, I used a series of files to slowly shave down to the exact size I
needed. Overall, if you can just laser cut it, you'll be cutting down your
build time by a major factor. If you must print it, keep a dremel and files
close at hand.

Wiring it was not too bad. Not having a motor shield isn't a big deal at all.
Just separating the battery supply from the arduino's power is enough (but
make sure to connect grounds, or else you'll get a floating voltage that could
fry something). The above link was all I needed to get it all hooked up. The
addition of a ping sensor is no big deal too. The only nuance is that you
_must_ connect it to the common ground between the motors and arduino.

Configuring the motors was the next part that got me stuck. Knowing that
_you must calibrate the motors_ to get good results from the IK can save
you much time and frustration. The calibration itself is very easy. The
last link from above describes it pretty well, except that they refer to some
mysterious module called a "MeBrain." Skip that. You can just hook in a
standard potentiometer. If you don't have one of those and you're feeling
pretty clever, you could certainly just use the Serial monitor to give
different PWM values to the motors with the arrow keys. So what is the
calibration? It's just matching PWM values on the arduino pins to angles
of the arm. Check out the config folder for more.

## The Particulars of Wiring

![Imgur](https://i.imgur.com/Q0pD60Z.jpg)
![Imgur](https://i.imgur.com/Tbu6QGD.jpg)

The wiring here is pretty close together. In fact, these pictures are pretty
useless. Instead, here's the wiring diagram:

![Imgur](https://i.imgur.com/l6jjfEe.png)

## Making it Angry: the Code

Overall, AngryBot is not very complex at all. It has two states: scanning
and attacking. The scanning state consists of looking in four predefined
locations. If at any point the sensor reads something that's close enough,
it'll go into the attacking state. The attacking state first checks if
the location is reachable. If it is, the arm sticks out and tries to
reach that point. Once it does reach that point it'll snap the gripper
(mouth) a few times for effect. You can see all of this code in the
_code_ folder.

Another small detail: I'm using `ino` to build and upload my code. Essentially
it's like an arduino build tool for the command line. That's how my code is
structured; the library is sym-linked into the `lib/` directory so I can use
the IK. Building and running this code can go like this:

```shell
$ cd code/
$ ino build
$ sudo ino upload
$ sudo ino serial
```

(You only need the serial part for configuration though.)

## What Now?

AngryBot was fun, but it's still not impressive enough to be really notable.
In the future, I'd like to deck it out a little bit. I'd like to have an RGB
LED on it that changes colors to red when it's gonna attack. I'd also like
to have multiple personalities. Maybe on a clock it changes from really
angry to really shy and runs away every time it sees something. That sort
of Jekyll and Hyde relationship could give the character a whole lot more
depth.

To make these changes, I think I'd have to laser cut the robot. For whatever
reason, the IK are off by a noticeable amount. I think the blocky construction
by 3D printer is too coarse to be controlled finely. Some errors in the lining
of up the gripper hands, for example, make the robot stop working correctly
after a few attempts at biting.

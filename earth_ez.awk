#!/usr/bin/gawk -f

BEGIN {
    extension("./awkgl.so", "dlload")
    #		     X    Y   Wid  Height
    SetWindowPosSize(200, 50, 1000, 700)
    #		  Window Title
    CreateWindow("AwkGL Demo Earth")
    TimerFunc(30, "timer", 0)
    Enable("POINT_SMOOTH")
    #Enable("LINE_SMOOTH")
    wire=0
    MainLoop()
}

function keyboard(key, x, y)
{
    switch (key) {
    case " ":
	wire = !wire
	break
    case "q":
    case "Q":
    case "\033":
	print "exiting..."
	exit
	break
    }
}

function reshape(width, height)
{
    Viewport(0, 0, width, height)
    MatrixMode("PROJECTION")
    LoadIdentity()
    Perspective(45, width/ height , 1, 2000)
    LookAt(-70.0, 280.0, 70.0,	0.0, 0.0, 0.0,	0.0, 0.0, 1.0)
    MatrixMode("MODELVIEW")
    LoadIdentity()
}

function timer(val)
{
    moon_ang = moon_ang >= 359 ? 0 : moon_ang + 1
    #PostRedisplay()
    TimerFunc(30, "timer", 0)
}

function display()
{
    ClearColor(10, 10, 10)
    LoadIdentity()

    DrawAxes(500)

    Color(32, 80, 207)
    if (wire) {
	WireSphere(35.0, 24, 18)	# Earth
    } else {
	SolidSphere(35.0, 24, 18)	# Earth
    }

    PushMatrix()
    Rotate(moon_ang, 0.0, 0.0, 1.0)	# z軸周りにmoon_ang度回転
    Translate(130.0, 0.0, 0.0)		# x軸に平行移動

    Color(255, 255, 64)
    if (wire) {
	WireSphere(5.0, 18, 12)		# Moon
    } else {
	SolidSphere(5.0, 18, 12)	# Moon
    }

    PopMatrix()
}


#!/usr/bin/gawk -f

BEGIN {
    str = "hello, world."

    extension("./awkgl.so", "dlload")
    #		     X    Y   Wid  Height
    SetWindowPosSize(450, 50, 400, 400)
    #		  Window Title
    CreateWindow("AwkGL Demo Hello")
    Enable("POINT_SMOOTH")
    MainLoop()
}

function display()
{
    ClearColor(10, 10, 10)
    LoadIdentity()

    DrawAxes(500)

    PushMatrix()
    #Rotate(moon_ang, 0.0, 0.0, 1.0)	# z軸周りにmoon_ang度回転
    #Translate(130.0, 0.0, 0.0)		# x軸に平行移動

    Color(255, 64, 255)

    RasterPos(0, 0, 0)
    for (i = 1; i <= length(str); i++) {
	BitmapCharacter("BITMAP_HELVETICA_12", substr(str, i))
    }
    StrokeString("STROKE_ROMAN", str)

    WindowPos(10, 380)
    for (i = 1; i <= length(str); i++) {
	BitmapCharacter("BITMAP_HELVETICA_12", substr(str, i))
    }

    PopMatrix()
}

function keyboard(key, x, y)
{
    switch (key) {
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

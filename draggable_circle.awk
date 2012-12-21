#!/usr/local/bin/gawk-4.0.0 -f

BEGIN {
    ObjW = 0.2
    ObjH = 0.2
    WindowWidth = 400
    WindowHeight = 400
    ViewRatio = 400.0

    extension("./awkgl.so", "dlload")

    #		     X    Y   Wid  Height
    SetWindowPosSize(450, 50, 400, 400)
    #		  Window Title
    CreateWindow("AwkGL Demo1")
    #(0-255)	 R   G    B
    ClearColor(21, 10, 89)
    #ReshapeFunc("reshape")
    KeyboardFunc("keyboard")
    SpecialFunc("special")
    #MouseFunc("mouse")
    MotionFunc("motion")
    #PassiveMotionFunc("passivemotion")
    DisplayFunc("display")
    MainLoop()
}

function reshape(w, h)
{
    Viewport(0, 0, w, h);
    LoadIdentity();
    Ortho(-w / 400.0, w / 400.0, -h / 400.0, h / 400.0, -1.0, 1.0);
    return;
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
    case "g":
	ClearColor(91, 100, 19)
	break
    case "r":
	ClearColor(191, 00, 9)
	break
    case "b":
	ClearColor(21, 10, 89)
	break
    case "h":
	ObjX -= 0.1
	break
    case "j":
	ObjY -= 0.1
	break
    case "k":
	ObjY += 0.1
	break
    case "l":
	ObjX += 0.1
	break
    }

    tmp = WindowWidth / ViewRatio
    if (ObjX - ObjW < -tmp) ObjX = - tmp + ObjW
    if (ObjX + ObjW >  tmp) ObjX =   tmp - ObjW
    tmp = WindowHeight / ViewRatio
    if (ObjY - ObjH < -tmp) ObjY = - tmp + ObjH
    if (ObjY + ObjH >  tmp) ObjY =   tmp - ObjH
}

function special(key, x, y)
{
    switch (key) {
    case "F1":
	print "exiting..."
	exit
	break
    case "left":
	break
    }
}

function mouse(button, state, x, y)
{
    #print button, state, x, y
}

function motion(x, y)
{
    #print x, y

    ObjX = (x - WindowWidth / 2) / (ViewRatio / 2)
    ObjY = (y - WindowHeight / 2) / (-ViewRatio / 2)

    tmp = WindowWidth / ViewRatio
    if (ObjX - ObjW < -tmp) ObjX = - tmp + ObjW
    if (ObjX + ObjW >  tmp) ObjX =   tmp - ObjW
    tmp = WindowHeight / ViewRatio
    if (ObjY - ObjH < -tmp) ObjY = - tmp + ObjH
    if (ObjY + ObjH >  tmp) ObjY =   tmp - ObjH
}

function passivemotion(x, y)
{
    #print "passive", x, y
}

function display()
{
    #Begin("TRIANGLE_FAN")
    Begin("POLYGON")
    #Begin("LINE_LOOP")
    Color(255.0, 255.0, 0.0) # 黄
    #Vertex2d(ObjX, ObjY)
    n = 36
    for (i = 0; i <= n; i++) {
	Vertex2d(ObjX - ObjW * cos(i * 360 / n * 3.14 / 180), \
		ObjY - ObjH * sin(i * 360 / n * 3.14 / 180))
    }
    End()
}

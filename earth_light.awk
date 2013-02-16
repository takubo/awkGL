BEGIN {
    extension("./awkgl.so", "dlload")
    #		     X    Y   Wid  Height
    SetWindowPosSize(250, 50, 600, 450)
    #		  Window Title
    CreateWindow("AwkGL Demo Earth")
    #(0-255)	 R   G    B
    ClearColor(0, 0, 0)
    ReshapeFunc("reshape")
    DisplayFunc("display")
    TimerFunc(50, "timer", 0)
    KeyboardFunc("keyboard")
    wire=0
    Enable("LIGHTING")
    MainLoop()
}

function keyboard(key, x, y)
{
    switch (key) {
    case " ":
	wire = !wire
	break
    case "a":
	aa ? Enable("LINE_SMOOTH") : Disable("LINE_SMOOTH")
	aa = !aa
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
    LookAt(-170.0, 280.0, 100.0,	0.0, 0.0, 0.0,	0.0, 0.0, 1.0)
    MatrixMode("MODELVIEW")
    LoadIdentity()

    #Light(0, "AMBIENT", )

    # Sun
    Light(0, "SPECULAR", 1, 1, 1, 1)
    Light(0, "DIFFUSE", 0.8, 0.8, 0.8, 1)
    #Light(0, "DIFFUSE", 0.1, 0.1, 0.1, 1)
    Light(0, "AMBIENT", 0.4, 0.4, 0.4, 1)
    #Light(0, "POSITION", 1, 0, 0, 1)
    Light(0, "POSITION", 100, 500, 0, 0)
    Light(0, "DIRECTION", 0, 0, 0)
}

function timer(val)
{
    moon_ang += 1.8
    moon_ang -= (moon_ang > 360) ? 360 : 0
    #PostRedisplay()
    TimerFunc(50, "timer", 0)
}

function display()
{
    ClearColor(0, 0, 0)
    LoadIdentity()

    #Material(32, 32, 255)
    Material("BOTH", "SHININESS", 32)
    Material("BOTH", "SPECULAR", 64/255*0.9, 128/255*0.9, 255/255*0.9, 1)
    Material("BOTH", "DIFFUSE", 64/255*0.52, 128/255*0.52, 255/255*0.52, 1)
    Material("BOTH", "AMBIENT", 64/255*0.22, 128/255*0.22, 255/255*0.22, 1)
    #Material("BOTH", "AMBIENT", 64/255*0.1, 128/255*0.1, 255/255*0.1, 1)
    if (wire) {
	WireSphere(45.0, 32, 32)	# Earth
    } else {
	SolidSphere(45.0, 32, 32)	# Earth
    }

    PushMatrix()
    Rotate(moon_ang, 0.0, 0.0, 1.0)	# z軸周りにmoon_ang度回転
    Translate(120.0, 0.0, 0.0)		# x軸に60平行移動

    #Color(255, 255, 64)
    Material("BOTH", "SHININESS", 3)
    Material("BOTH", "SPECULAR", 255/255*0.6, 255/255*0.6, 64/255*0.6, 1)
    Material("BOTH", "DIFFUSE", 255/255*0.4, 255/255*0.4, 64/255*0.4, 1)
    #Material("BOTH", "AMBIENT", 255/255*0.2, 255/255*0.2, 128/255*0.2, 1)
    Material("BOTH", "AMBIENT", 255/255*0.1, 255/255*0.1, 128/255*0.1, 1)
    if (wire) {
	WireSphere(8.0, 16, 10)		# Moon
    } else {
	SolidSphere(8.0, 16, 10)	# Moon
    }

    PopMatrix()
}


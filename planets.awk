#!/usr/bin/gawk -f

BEGIN {
    base_ang = 1
    base_time = 30

    orbit = 1
}

/^\w/ {
    name = $1
    obj[name]["distance"] = $2 * 100
    obj[name]["radius"]   = $3
    obj[name]["cycle"]    = $4
    #obj[name]["red"]      = $5
    #obj[name]["green"]    = $6
    #obj[name]["blue"]     = $7
    obj[name]["red"]      = strtonum("0x" substr($5, 2, 2))
    obj[name]["green"]    = strtonum("0x" substr($5, 4, 2))
    obj[name]["blue"]     = strtonum("0x" substr($5, 6, 2))

    obj[name]["notch"] = 1 / obj[name]["cycle"] * base_ang
    #obj[name]["ang"]
}

END {
    extension("./awkgl.so", "dlload")

    #		     X    Y   Wid  Height
    SetWindowPosSize(200, 50, 1000, 700)
    #		  Window Title
    CreateWindow("Planets Simulator")

    Enable("POINT_SMOOTH")
    #Enable("LINE_SMOOTH")

    #(0-255)   R   G    B
    ClearColor(10, 10, 10)

    TimerFunc(base_time, "timer", 0)
    MainLoop()
}

function keyboard(key, x, y)
{
    switch (key) {
    case " ":
	orbit = !orbit
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
    #MatrixMode(GL_PROJECTION)
    #LoadIdentity()
    Perspective(45, width/ height , 1, 2000)
    LookAt(-70.0, 280.0, 80.0,	0.0, 0.0, 0.0,	0.0, 0.0, 1.0)
    #MatrixMode( GL_MODELVIEW )
    LoadIdentity()
}

function timer(val,    i, tmp)
{
    for (i in obj) {
	obj[i]["ang"] = (obj[i]["ang"] + obj[i]["notch"]) % 360
	#tmp = obj[i]["obj"] + obj[i]["notch"]
	#obj["ang"] = tmp < 360 ? tmp : tmp - 360
    }

    TimerFunc(base_time, "timer", 0)
}

function display(    i)
{
    ClearColor(10, 10, 10)
    LoadIdentity()

    for (i in obj) {
	if (orbit) {
	    Color(255.0, 255.0, 255.0)
	    DrawCircle(obj[i]["distance"], 120, 0)
	}

	PushMatrix()

	Rotate(obj[i]["ang"], 0.0, 0.0, 1.0)		# z軸周りにang度回転
	Translate(obj[i]["distance"], 0.0, 0.0)		# x軸に平行移動

	Color(obj[i]["red"], obj[i]["green"], obj[i]["blue"])

	WireSphere(obj[i]["radius"], 18, 12)

	PopMatrix()
    }
}

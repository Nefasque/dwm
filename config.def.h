/* See LICENSE file for copyright10 and license details. */

/* appearance */
static unsigned int borderpx  = 2;        /* border pixel of windows */
static unsigned int gappx     = 3;        /* gaps between windows */
static unsigned int snap      = 32;       /* snap pixel */
static int showbar            = 1;        /* 0 means no bar */
static int topbar             = 1;        /* 0 means bottom bar */
static char font[]            = "Fira Code Nerd Font:size=10";
static char dmenufont[]       = "Fira Code Nerd Font:size=10";
static const char *fonts[]          = { font };

static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */


/* color */
static char color0[]           = "#272822";
static char color1[]           = "#f92672";
static char color2[]           = "#a6e22e";
static char color3[]           = "#f4bf75";
static char color4[]           = "#66d9ef";
static char color5[]           = "#ae81ff";
static char color6[]           = "#a1efe4";
static char color7[]           = "#f8f8f2";

static char gray1[]            = "#222222";
static char gray2[]            = "#444444";
static char gray3[]            = "#888888";
static char gray4[]            = "#eeeeee";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { gray3, color0, gray2 },
       [SchemeSel]  = { gray4, color0, color1  },
       [SchemeStatus]={ gray4, color0, NULL  },
};


/* status bar */
static const Block blocks[] = {
	/* fg     command				interval	signal */
	{ color1, "sb-clock",			60,		1},
  { color2, "sb-volume",    0,    1},
  { color3, "sb-kbselect",  0,    1},
	{ color6, "sb-pacpackages",			177000,		1}
  // { color4, "sb-memory",    30,    1},
	// { gray1, "sb-disk",				9000,		2},
	// { gray2, "sb-battery",			10,		3},
	// { gray3, "sb-internet",			10,		4},
	// { cyan, "sb-mailbox",			0,		5},
	// { "#000001", "sb-moonphase",			0,		6},
	// { "#1F0077", "sb-forecast",			0,		7},
	// { "#000077", "sb-volume",			0,		8},
	// { "#177000", "sb-sync",				0,		10},
  // { gray1, "sb-mpc",				0,		26},
	// { gray2, "sb-music",			0,		11},
  // { gray3, "sb-tasks",			10,		12},
	// { gray4, "sb-notes",			0,		13},
	// { cyan, "echo '';cat /tmp/recordingicon",	0,		14},
};

/* inverse the order of the blocks, comment to disable */
#define INVERSED	1
/* delimeter between blocks commands. NULL character ('\0') means no delimeter. */
static char delimiter[] = " ";
/* max number of character that one block command can output */
#define CMDLENGTH	50





static char *tagsel[][2] = {
   /*   fg         bg    */
  { gray3, color0 }, /* norm */
  { color0, color1 }, /* sel */
  { gray4,  color0 }, /* occ but not sel */
  { color1,  color5 }, /* has pinned tag */
};
/* tagging */
static const char *tags[] = { "󰆍", "", "", "󰭹", "", "", "", "", "", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "  ",      tile },    /* first entry is default */
	{ "  ",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenucmd[] = { "dmenu_run", "-fn", dmenufont, "-nb", color0, "-nf", color1, "-sb", color0, "-sf", color1, NULL };
static const char *j4_dmenu_desktop[] = { "j4-dmenu-desktop", NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *firefox[]  = { "firefox", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */

  // app
	{ MODKEY|ShiftMask,             XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_d,      spawn,          {.v = j4_dmenu_desktop } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
  // open firefox
	{ MODKEY|ShiftMask,             XK_b, spawn,          {.v = firefox } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
  { MODKEY|ShiftMask,             XK_k,      pushdown,       {0} },
	{ MODKEY|ShiftMask,             XK_j,      pushup,         {0} },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_p,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_w,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,             XK_m,      setlayout,      {.v = &layouts[2]} }, 
  { MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	TAGKEYS(                        XK_0,                      9)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkStatusText,        0,              Button1,        sendstatusbar,   {.i = 1 } },
	{ ClkStatusText,        0,              Button2,        sendstatusbar,   {.i = 2 } },
	{ ClkStatusText,        0,              Button3,        sendstatusbar,   {.i = 3 } },
	{ ClkStatusText,        0,              Button4,        sendstatusbar,   {.i = 4 } },
	{ ClkStatusText,        0,              Button5,        sendstatusbar,   {.i = 5 } },
	{ ClkStatusText,        ShiftMask,      Button1,        sendstatusbar,   {.i = 6 } },

	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

/*
* Xresources preferences to load at startup
*/
ResourcePref resources[] = {
		{ "font",               STRING,  &font },
		{ "dmenufont",          STRING,  &dmenufont },
		{ "gray1",              STRING,  &gray1 },
		{ "gray2",              STRING,  &gray2 },
		{ "gray3",              STRING,  &gray3 },
		{ "gray4",              STRING,  &gray4 },
    { "color0",             STRING,  &color0 },
		{ "color1",             STRING,  &color1 },
    { "color2",             STRING,  &color2 },
    { "color3",             STRING,  &color3 },
    { "color4",             STRING,  &color4 },
    { "color5",             STRING,  &color5 },
    { "color6",             STRING,  &color6 },
    { "color7",             STRING,  &color7 },
		{ "borderpx",          	INTEGER, &borderpx },
    { "gappx",            	INTEGER, &gappx },
		{ "snap",           		INTEGER, &snap },
		{ "showbar",          	INTEGER, &showbar },
		{ "topbar",           	INTEGER, &topbar },
		{ "nmaster",          	INTEGER, &nmaster },
		{ "resizehints",       	INTEGER, &resizehints },
		{ "mfact",          	 	FLOAT,   &mfact },
};




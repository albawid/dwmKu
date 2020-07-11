/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 5;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Iosevka Nerd Font:size=11:style=Regular" "Material Design Icons Desktop:size=12:style=Regular" "Noto Sans CJK JP:size=12:style=Regular" };
static const char dmenufont[]       = "Iosevka Nerd Font:size=11";
static const char col_gray1[]       = "#1b2b34";
static const char col_gray2[]       = "#4f5866";
static const char col_gray3[]       = "#c0c5ce";
static const char col_violet[]      = "#c594c5";
static const char col_blue[]        = "#6699cc";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_violet },
	[SchemeSel]  = { col_gray2, col_gray1,  col_blue  },
	[SchemeStatus]  = { col_gray3, col_gray1,  "#000000"  }, // Statusbar right {text,background,not used but cannot be empty}
	[SchemeTagsSel]  = { col_blue, col_gray1,  "#000000"  }, // Tagbar left selected {text,background,not used but cannot be empty}
    [SchemeTagsNorm]  = { col_violet, col_gray1,  "#000000"  }, // Tagbar left unselected {text,background,not used but cannot be empty}
    [SchemeInfoSel]  = { col_gray3, col_gray1,  "#000000"  }, // infobar middle  selected {text,background,not used but cannot be empty}
    [SchemeInfoNorm]  = { col_gray3, col_gray1,  "#000000"  }, // infobar middle  unselected {text,background,not used but cannot be empty}
};

/* tagging */
/* static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" }; */
static const char *tags[] = { "一", "二", "三", "四", "五", "六", "七", "八", "九" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class              instance            title                     tags mask     isfloating   monitor */
  /* Floating */
	{ "Connman-gtk",     "connman-gtk",       "Network Settings",       0,            1,           -1 },
	{ "Xarchiver",       "xarchiver",         NULL,                     0,            1,           -1 },
	{ "mpv",             NULL,                NULL,                     0,            1,           -1 },
	{ "Virt-manager",    "virt-manager",      NULL,                     0,            1,           -1 },
	{ "PCSX2",           NULL,                NULL,                     0,            1,           -1 },
	{ "feh",             NULL,                NULL,                     0,            1,           -1 },

  /* Non-Floating */
	{ "qutebrowser",     "qutebrowser",       "qutebrowser",            1 << 1,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
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
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_blue, "-sf", col_gray1, NULL };
static const char *termcmd[]  = { "st", NULL };

#include <X11/XF86keysym.h>
/* Volume Control */
static const char *vol_up[]   = { "amixer", "set", "Master", "5+",     NULL };
static const char *vol_down[] = { "amixer", "set", "Master", "5-",     NULL };
static const char *vol_mute[] = { "amixer", "set", "Master", "toggle",  NULL };

/* Brightness Control */
static const char *bri_up[]       = {"light", "-A", "5", NULL};
static const char *bri_down[]     = {"light", "-U", "5", NULL};

#include "movestack.c"
static Key keys[] = {
	/* modifier                     key        function        argument */

/* Volume Control */
  { 0,                       XF86XK_AudioLowerVolume, spawn, {.v = vol_down } },
	{ 0,                       XF86XK_AudioMute, spawn, {.v = vol_mute } },
	{ 0,                       XF86XK_AudioRaiseVolume, spawn, {.v = vol_up   } },

/* Brightness Control */
  { 0,                            XF86XK_MonBrightnessUp,	  spawn,		{.v = bri_up } },
  { 0,                            XF86XK_MonBrightnessDown,	spawn,		{.v = bri_down } },

/* Shortcut */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_o,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_h,      setcfact,       {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_l,      setcfact,       {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_o,      setcfact,       {.f =  0.00} },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_s,      togglesticky,   {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
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
	{ MODKEY|ShiftMask,             XK_r,      quit,           {0} },

  /* Custom Keybindings */
  /* modifier                     key                        function        argument */
  { MODKEY|ShiftMask,             XK_x,                      spawn,          SHCMD("betterlockscreen -l dimblur -t 'Enter Nuclear Code...'") },
  { MODKEY|ShiftMask,             XK_y,                      spawn,          SHCMD("/.local/bin/dmenu_ytview") },
  { MODKEY,                       XK_F1,                     spawn,          SHCMD("/.local/bin/dmenu_record") },
  { MODKEY,                       XK_F2,                     spawn,          SHCMD("/usr/bin/qutebrowser") },
  { MODKEY|ShiftMask,             XK_F2,                     spawn,          SHCMD("/usr/bin/google-chrome-stable") },
  { MODKEY,                       XK_F3,                     spawn,          SHCMD("/usr/bin/thunar") },
  { MODKEY,                       XK_F4,                     spawn,          SHCMD(".local/bin/dmenu_monitor") },
  { MODKEY,                       XK_F12,                    spawn,          SHCMD("/usr/bin/connman-gtk") },
  { MODKEY,                       XK_End,                    spawn,          SHCMD(".local/bin/dmenu_power") },
  { MODKEY,                       XK_Print,                  spawn,          SHCMD("scrot -ube 'mv $f ~/Picture/Screenshots/'") },
  { MODKEY|ControlMask,           XK_Print,                  spawn,          SHCMD("scrot -e 'mv $f ~/Picture/Screenshots/'") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};


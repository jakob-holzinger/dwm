/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx = 1; /* border pixel of windows */
static const unsigned int snap = 32;    /* snap pixel */
static const int showbar = 1;           /* 0 means no bar */
static const int topbar = 1;            /* 0 means bottom bar */
static const char *fonts[] = {"FiraCode Nerd Font:size=18"};
static const char dmenufont[] = "FiraCode Nerd Font:size=18";
static const char col_bg[] = "#1c1f26";     // normal background
static const char col_fg[] = "#e0e6f0";     // highlighted text
static const char col_border[] = "#6caed9"; // highlighted background
static const char col_gray[] = "#aab8c5";   // normal text
static const char col_lightblue[] = "#a7cfdc";
static const char *colors[][3] = {
    /*               fg         bg         border   */
    [SchemeNorm] = {col_gray, col_bg, col_bg},
    [SchemeSel] = {col_fg, col_border, col_border},
};

/* tagging */
static const char *tags[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};

#include "shiftview.c"

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class      instance    title       tags mask     isfloating   monitor */
    {"Gimp", NULL, NULL, 0, 1, -1},
    {"Firefox", NULL, NULL, 1 << 8, 0, -1},
};

/* layout(s) */
static const float mfact = 0.55;     /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;        /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
    /* symbol     arrange function */
    {"[]=", tile}, /* first entry is default */
    {"><>", NULL}, /* no layout function means floating behavior */
    {"[M]", monocle},
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY, TAG)                                                                          \
    {MODKEY, KEY, view, {.ui = 1 << TAG}},                                                         \
        {MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}},                                 \
        {MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},                                          \
        {MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                                                                 \
    {                                                                                              \
        .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                                       \
    }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {"dmenu_run", "-m",   dmenumon, "-fn",    dmenufont,
                                 "-nb",       col_bg, "-nf",    col_gray, "-sb",
                                 col_border,  "-sf",  col_fg,   NULL};
static const char *termcmd[] = {"st", NULL};
static const char *snipcmd[] = {"sh", "-c",
                                "FILE=~/pictures/screenshots/$(date +%F_%T).png; maim -s \"$FILE\" "
                                "&& xclip -selection clipboard -t image/png -i < \"$FILE\"",
                                NULL};
static const char *filemgrcmd[] = {"thunar", NULL};
static const char *brightnessupcmd[] = { "brightnessctl", "set", "10%+", NULL };
static const char *brightnessdowncmd[] = { "brightnessctl", "set", "10%-", NULL };

static const Key keys[] = {
    /* modifier                     key        function        argument */
    {MODKEY, XK_s, spawn, {.v = dmenucmd}},
    {MODKEY, XK_Return, spawn, {.v = termcmd}},
    {MODKEY, XK_b, togglebar, {0}},
    {MODKEY, XK_j, focusstack, {.i = +1}},
    {MODKEY, XK_k, focusstack, {.i = -1}},
    {MODKEY, XK_i, incnmaster, {.i = +1}},
    {MODKEY, XK_d, incnmaster, {.i = -1}},
    {MODKEY, XK_h, setmfact, {.f = -0.05}},
    {MODKEY, XK_l, setmfact, {.f = +0.05}},
    {MODKEY, XK_Return, zoom, {0}},
    {MODKEY, XK_Tab, view, {0}},
    {MODKEY, XK_q, killclient, {0}},
    {MODKEY, XK_t, setlayout, {.v = &layouts[0]}},
    {MODKEY, XK_f, setlayout, {.v = &layouts[1]}},
    {MODKEY, XK_m, setlayout, {.v = &layouts[2]}},
    {MODKEY, XK_space, setlayout, {0}},
    {MODKEY | ShiftMask, XK_space, togglefloating, {0}},
    {MODKEY, XK_0, view, {.ui = ~0}},
    {MODKEY | ShiftMask, XK_0, tag, {.ui = ~0}},
    {MODKEY, XK_comma, focusmon, {.i = -1}},
    {MODKEY, XK_period, focusmon, {.i = +1}},
    {MODKEY | ShiftMask, XK_comma, tagmon, {.i = -1}},
    {MODKEY | ShiftMask, XK_period, tagmon, {.i = +1}},
    {MODKEY, XK_Left, shiftview, {.i = -1}},
    {MODKEY, XK_Right, shiftview, {.i = +1}},
    {MODKEY | ShiftMask, XK_s, spawn, {.v = snipcmd}},
    {MODKEY, XK_e, spawn, {.v = filemgrcmd}},
    {MODKEY, XK_BackSpace, spawn, SHCMD("/home/jakob/.config/dwm/powermenu.sh")},
    {0, XF86XK_AudioRaiseVolume, spawn, SHCMD("pamixer -i 5")},
    {0, XF86XK_AudioLowerVolume, spawn, SHCMD("pamixer -d 5")},
    {0, XF86XK_AudioMute, spawn, SHCMD("pamixer -t")},
    { 0, XF86XK_MonBrightnessUp,   spawn, {.v = brightnessupcmd } },
    { 0, XF86XK_MonBrightnessDown, spawn, {.v = brightnessdowncmd } },
    TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2) TAGKEYS(XK_4, 3) TAGKEYS(XK_5, 4)
        TAGKEYS(XK_6, 5) TAGKEYS(XK_7, 6) TAGKEYS(XK_8, 7)
            TAGKEYS(XK_9, 8){MODKEY | ShiftMask, XK_q, quit, {0}},
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
    /* click                event mask      button          function        argument */
    {ClkLtSymbol, 0, Button1, setlayout, {0}},
    {ClkLtSymbol, 0, Button3, setlayout, {.v = &layouts[2]}},
    {ClkWinTitle, 0, Button2, zoom, {0}},
    {ClkStatusText, 0, Button2, spawn, {.v = termcmd}},
    {ClkClientWin, MODKEY, Button1, movemouse, {0}},
    {ClkClientWin, MODKEY, Button2, togglefloating, {0}},
    {ClkClientWin, MODKEY, Button3, resizemouse, {0}},
    {ClkTagBar, 0, Button1, view, {0}},
    {ClkTagBar, 0, Button3, toggleview, {0}},
    {ClkTagBar, MODKEY, Button1, tag, {0}},
    {ClkTagBar, MODKEY, Button3, toggletag, {0}},
};

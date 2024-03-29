\ProvidesClass{customClass}

\LoadClass[a4paper,12pt]{report} % Classe du document

%--------------------- Packages ------------------------

\RequirePackage[section]{placeins} % Pour placement de section


\RequirePackage{mathtools} %Paquet pour des équations et symboles mathématiques

% Include all the packages, authors, etc..
% \usepackage{babel}
% \usepackage{hyphsubst}  % For hyphen babel error
\RequirePackage[utf8]{inputenc} % Caractères spéciaux
\usepackage[T1]{fontenc}
\usepackage{xspace}
%\usepackage[cyr]{aeguill}
\usepackage[french]{babel}

\RequirePackage{graphicx} %Paquet pour insérer des images
\RequirePackage{float} %Pour placement d'images

\RequirePackage[justification=centering]{caption} % Pour les légendes centralisées
\RequirePackage{subcaption}
\usepackage{packages/wallpaper}
%\RequirePackage{nomencl}

%\makenomenclature
\RequirePackage{fancyhdr}
\usepackage{packages/lastpage}
%\pagestyle{fancy}
%\fancyheadoffset{1cm}
%\setlength{\headheight}{2cm}
\RequirePackage{url}
\RequirePackage[hidelinks]{hyperref}%Paquet pour insérer légendes dans des sous-figures comme Figure 1a, 1b
%Configuration de la page
\RequirePackage{enumitem}

%affichage image pgf
\usepackage{pgf}
\usepackage{lmodern}

% Adds unnumbered sectoin
\usepackage{titletoc}

% Math
\usepackage{amsmath, amssymb}
\newtheorem{defi}{Définition}

% Code
% \usepackage{listings}
\usepackage[final]{listings}
\lstdefinestyle{code}{
  belowcaptionskip=1\baselineskip,
  breaklines=true,
  frame=L,
  xleftmargin=\parindent,
  language=C,
  showstringspaces=false,
  basicstyle=\footnotesize\ttfamily,
  keywordstyle=\bfseries\color{green!40!black},
  commentstyle=\itshape\color{purple!40!black},
  identifierstyle=\color{blue},
  stringstyle=\color{orange},
}
\lstset{style=code, language=C}

\usepackage{xcolor}

\usepackage{hyperref}

% Algortihmes
%\usepackage[vlined,lined,linesnumbered,boxed,french]{algorithm2e}
%\DeclareMathOperator*{\argmin}{argmin}
%\DeclareMathOperator{\myfunc}{myfunc}
%\DeclareMathOperator*{\sign}{sign}
%\DeclareMathOperator*{\imwh}{width}
%\DeclareMathOperator*{\imht}{height}

% Extra
\usepackage[left=2.5cm,right=2.5cm,top=2cm,bottom=2cm]{geometry}

% Figures
\usepackage{graphicx}
\usepackage{float}  % better figure placement, have no idea of what im doing


\renewcommand\thesection{\Roman{section}}
\renewcommand\thesubsection{\hspace{1em}\arabic{subsection}}

\RequirePackage{titlesec}

\setcounter{secnumdepth}{4}

\titleformat{\paragraph}
{\normalfont\normalsize\bfseries}{\theparagraph}{1em}{}
\titlespacing*{\paragraph}
{1.5em}{3.25ex plus 1ex minus .2ex}{1.5ex plus .2ex}

\renewcommand\theparagraph{\hspace{1em}\alph{paragraph}}

\newcommand{\code}[1]{\texttt{#1}}


%color box


\usepackage[most]{tcolorbox}

\newtcolorbox[auto counter]{summary}[1][]{title={\bfseries Remarque~\thetcbcounter},enhanced,drop shadow={black!50!white},
  coltitle=black,
  top=0.1in,
  attach boxed title to top right=
  {xshift=0pt},
  boxed title style={size=small,colback=pink},#1}
%
%-------------------- Informations sur le rapport ----------------------
%

\newcommand{\sujetprojet}[1]{\renewcommand{\sujetprojet}{#1}}
\newcommand{\lieuprojet}[1]{\renewcommand{\lieuprojet}{#1}}
\newcommand{\basdepage}[1]{\renewcommand{\basdepage}{#1}}

\newcommand{\titre}[1]{\renewcommand{\titre}{#1}}

\newcommand{\eleve}[1]{\renewcommand{\eleve}{#1}}

\newcommand{\ensref}[1]{\renewcommand{\ensref}{#1}}
\newcommand{\tuteurentreprise}[1]{\renewcommand{\tuteurentreprise}{#1}}

\newcommand{\logoentreprise}[1]{\renewcommand{\logoentreprise}{#1}}

\newcommand{\dates}[1]{\renewcommand{\dates}{#1}}
\newcommand{\shortdates}[1]{\renewcommand{\shortdates}{#1}}

\newcommand{\fairemarges}{

\pagestyle{fancy}
\fancyheadoffset{1cm}
\setlength{\headheight}{20pt}


\lhead{\includegraphics[scale=0.03]{img/logoecole.png}\hspace{0.5em}}
\chead{\shortdates}
\rhead{\nouppercase{\leftmark}}
\rfoot{Page \thepage/\pageref{LastPage}}
\cfoot{\textbf{\basdepage}}
\lfoot{\lieuprojet}

}

\newcommand{\mainPage}{
\begin{titlepage}
\ThisURCornerWallPaper{0.5}{img/URC-gfx.png}
\ThisLLCornerWallPaper{0.4}{img/LLC-gfx.png}

\centering %Centraliser le contenu

% Logo Enseirb
\begin{figure}
    \begin{subfigure}{.5\textwidth}
        \centering
        \includegraphics[width=1\textwidth]{img/logoecole.png}\par\vspace{1cm} %Insertion du logo enseirb
    \end{subfigure}
\end{figure}

\vspace{10cm}
% Titre du rapport
\rule{\linewidth}{0.2 mm} \\[0.4 cm]
{\huge\bfseries \titre \par} \
\rule{\linewidth}{0.2 mm} \\[1.0 cm]

% Nom de l'étudiant
{\scshape\LARGE \eleve \par} 
\vspace{1.0cm}

% Parcours de l'étudiant
{\scshape Sujet : \sujetprojet} 
\vspace{0.5cm}

% Dates
{\large \dates \par} 
	

\end{titlepage}
    \newpage
}

\newcommand{\tabledematieres}{
    \tableofcontents
    \newpage
}

\newcommand{\insererfigure}[4]{
    \begin{figure}[!ht]
        \centering
        \includegraphics[height=#2]{#1}
        \caption{#3}
        \label{fig: #4}
    \end{figure}
}


% paragraph style
\parskip=4pt plus 1pt
\parindent=15pt

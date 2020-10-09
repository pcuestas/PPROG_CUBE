#include "cube.h"
#include <string.h>


/********DECLARATION OF AUXILIAR FUNCTIONS********/

/*function equivalent to: p[]=[a,b,c]*/
void assign(short *p, short a, short b, short c);

/*helps with the initialization: given a piece, it paints it so that the cube is solved when initialized*/

void paint_piece(Piece *pc);

/***************ROTATION OF A PIECE*****************/

/**
 * @brief rotates piece around x axis
 * @param p piece to be rotated
 * @param dir direction in which the rotation is made 
 *      dir=+-1 positive dir means piece is rotated clockwise 
 *      (from the positive x perspective)
 * 
 * dir==1  ==> (x,y,z)>>>(x,z,-y)
 * dir==-1 ==> (x,y,z)>>>(x,-z,y)
*/
void rot_x(Piece *p, short dir);

/**
 * @brief rotates piece around y axis
 * @param p piece to be rotated
 * @param dir direction in which the rotation is made 
 *      dir=+-1 positive dir means piece is rotated clockwise 
 *      (from the positive y perspective)
 * 
 * dir==1  ==> (x,y,z)>>>(-x,y,x)
 * dir==-1 ==> (x,y,z)>>>(x,y,-z)
*/
void rot_y(Piece *p, short dir);

/**
 * @brief rotates piece around z axis
 * @param p piece to be rotated
 * @param dir direction in which the rotation is made 
 *      dir=+-1 positive dir means piece is rotated clockwise 
 *      (from the positive z perspective)
 * 
 * dir==1  ==> (x,y,z)>>>(y,-x,z)
 * dir==-1 ==> (x,y,z)>>>(-y,x,z)
*/
void rot_z(Piece *p, short dir);



/***********MOVES*************/

/* @brief moves the upper layer clockwise */
void m_U(Cube3* c);

/* @brief moves the upper layer counterclockwise */
void m_u(Cube3* c);

/* @brief moves the lower layer clockwise */
void m_D(Cube3* c);

/* @brief moves the lower layer counterclockwise */
void m_d(Cube3* c);

/* @brief moves the right layer clockwise */
void m_R(Cube3* c);

/* @brief moves the right layer counterclockwise */
void m_r(Cube3* c);

/* @brief moves the left layer clockwise */
void m_L(Cube3* c);

/* @brief moves the left layer counterclockwise */
void m_l(Cube3* c);

/* @brief moves the front layer clockwise */
void m_F(Cube3* c);

/* @brief moves the front layer counterclockwise */
void m_f(Cube3* c);

/* @brief moves the back layer clockwise */
void m_B(Cube3* c);

/* @brief moves the back layer counterclockwise */
void m_b(Cube3* c);


/* @brief the layer between L and R, turn direction as L (top-down)*/
void m_M(Cube3* c);

void m_m(Cube3* c);

/* @brief the layer between U and D, turn direction as D (left-right)*/
void m_E(Cube3* c);

void m_e(Cube3* c);

/* @brief the layer between F and B, turn direction as F*/
void m_S(Cube3* c);

void m_s(Cube3* c);



/*the following functions consider different axis than we do in the cube.c for the auxiliary functions. No problem. This will be taken into account*/

/* @brief rotate the entire Cube on R*/
void m_X(Cube3* c);

void m_x(Cube3* c);

/* @brief rotate the entire Cube on U*/
void m_Y(Cube3* c);

void m_y(Cube3* c);

/* @brief rotate the entire Cube on F*/
void m_Z(Cube3* c);

void m_z(Cube3* c);





/***********functions in cube.h***************/

Cube3 *c_init(){
  Cube3 *c=NULL;
  short i;
  
  if(!(c=(Cube3*)malloc(sizeof(Cube3)))){
    return NULL;
  }
  
  /*center pieces:*/
  
  /*white centerpiece*/
  assign(c->pc[0].p,0,0,1);
  /*red centerpiece*/
  assign(c->pc[1].p,0,1,0);
  /*green centerpiece*/
  assign(c->pc[2].p,1,0,0);
  /*yellow centerpiece*/
  assign(c->pc[3].p,0,0,-1);
  /*orange centerpiece*/
  assign(c->pc[4].p,0,-1,0);
  /*blue centerpiece*/
  assign(c->pc[5].p,-1,0,0);
  
  /*edges:*/
  /*wg*/
  assign(c->pc[6].p,1,0,1);
  /*wr*/
  assign(c->pc[7].p,0,1,1);
  /*wb*/
  assign(c->pc[8].p,-1,0,1);
  /*wo*/
  assign(c->pc[9].p,0,-1,1);

  /*gr*/
  assign(c->pc[10].p,1,1,0);
  /*br*/
  assign(c->pc[11].p,-1,1,0);
  /*bo*/
  assign(c->pc[12].p,-1,-1,0);
  /*go*/
  assign(c->pc[13].p,1,-1,0);

  /*yg*/
  assign(c->pc[14].p,1,0,-1);
  /*yr*/
  assign(c->pc[15].p,0,1,-1);
  /*yb*/
  assign(c->pc[16].p,-1,0,-1);
  /*yo*/
  assign(c->pc[17].p,0,-1,-1);
  
  /*corners:*/
  /*wgr*/
  assign(c->pc[18].p,1,1,1);
  /*wbr*/
  assign(c->pc[19].p,-1,1,1);
  /*wbo*/
  assign(c->pc[20].p,-1,-1,1);
  /*wgo*/
  assign(c->pc[21].p,1,-1,1);

  /*ygr*/
  assign(c->pc[22].p,1,1,-1);
  /*ybr*/
  assign(c->pc[23].p,-1,1,-1);
  /*ybo*/
  assign(c->pc[24].p,-1,-1,-1);
  /*ygo*/
  assign(c->pc[25].p,1,-1,-1);

  for(i=0;i<NPC;i++){
    paint_piece(&(c->pc[i]));
  }

  return c;
}

void c_free(Cube3* c){
  free(c);
}

int c_iofPos(Cube3 *c, short x, short y, short z){
  short i;

  for(i=0;i<NPC;i++){
    if(c->pc[i].p[0]==x && c->pc[i].p[1]==y && c->pc[i].p[2]==z){
      return i;
    }
  }
  return -1;
}

int c_iofCol(Cube3 *c, short searchcolours){
  short i;

  for(i=0;i<NPC;i++){
    if(c->pc[i].c[0]+c->pc[i].c[1]+c->pc[i].c[2] == searchcolours){
      return i;
    }
  }
  return -1;
}


int p_print(FILE *f, Piece *p){
    if(!p||!f){
        return -1;
    }
    return fprintf(f,"\nPiece: pos=(%hd,%hd,%hd), col=(%hd,%hd,%hd)\n",p->p[0],p->p[1],p->p[2],p->c[0],p->c[1],p->c[2]);
}

/*Functions that call moves*/

void c_make(Cube3 *c, char l){
  if(l==' '){
    return ;
  }
  switch(l){
    case 'U':   m_U(c);   break;
    case 'u':   m_u(c);   break;
    case 'D':   m_D(c);   break;
    case 'd':   m_d(c);   break;
    case 'R':   m_R(c);   break;
    case 'r':   m_r(c);   break;
    case 'L':   m_L(c);   break;
    case 'l':   m_l(c);   break;
    case 'F':   m_F(c);   break;
    case 'f':   m_f(c);   break;
    case 'B':   m_B(c);   break;
    case 'b':   m_b(c);   break;

    case 'M':   m_M(c);   break;
    case 'm':   m_m(c);   break;
    case 'E':   m_E(c);   break;
    case 'e':   m_e(c);   break;    
    case 'S':   m_S(c);   break;
    case 's':   m_s(c);   break;

    case 'X':   m_X(c);   break;
    case 'x':   m_x(c);   break;
    case 'Y':   m_Y(c);   break;
    case 'y':   m_y(c);   break;    
    case 'Z':   m_Z(c);   break;
    case 'z':   m_z(c);   break;
    default: break;
  }
}

Status c_moves(Cube3 *c, char *s){
  int i, len;

  if(!s||!c){return ERROR;
  }
  
  len=strlen(s);

  for(i=0;i<len;i++){
    c_make(c, s[i]);
  }

  return OK;
}

/*CUBE MOVES*/

void m_U(Cube3* c){
  short i;

  for (i=0;i<NPC;i++){
    if(c->pc[i].p[2]==1){
      rot_z(&c->pc[i], 1);
    }
  }
}


void m_u(Cube3* c){
  short i;

  for (i=0;i<NPC;i++){
    if(c->pc[i].p[2]==1){
      rot_z(&c->pc[i], -1);
    }
  }
}


void m_D(Cube3* c){
  short i;

  for (i=0;i<NPC;i++){
    if(c->pc[i].p[2]==-1){
      rot_z(&c->pc[i], -1);
    }
  }
}


void m_d(Cube3* c){
  short i;

  for (i=0;i<NPC;i++){
    if(c->pc[i].p[2]==-1){
      rot_z(&c->pc[i], 1);
    }
  }
}


void m_R(Cube3* c){
  short i;

  for (i=0;i<NPC;i++){
    if(c->pc[i].p[1]==1){
      rot_y(&c->pc[i], 1);
    }
  }
}


void m_r(Cube3* c){
  short i;

  for (i=0;i<NPC;i++){
    if(c->pc[i].p[1]==1){
      rot_y(&c->pc[i], -1);
    }
  }
}


void m_L(Cube3* c){
  short i;

  for (i=0;i<NPC;i++){
    if(c->pc[i].p[1]==-1){
      rot_y(&c->pc[i], -1);
    }
  }
}


void m_l(Cube3* c){
  short i;

  for (i=0;i<NPC;i++){
    if(c->pc[i].p[1]==-1){
      rot_y(&c->pc[i], 1);
    }
  }
}


void m_F(Cube3* c){
  short i;

  for (i=0;i<NPC;i++){
    if(c->pc[i].p[0]==1){
      rot_x(&c->pc[i], 1);
    }
  }
}


void m_f(Cube3* c){
  short i;

  for (i=0;i<NPC;i++){
    if(c->pc[i].p[0]==1){
      rot_x(&c->pc[i], -1);
    }
  }
}


void m_B(Cube3* c){
  short i;

  for (i=0;i<NPC;i++){
    if(c->pc[i].p[0]==-1){
      rot_x(&c->pc[i], -1);
    }
  }
}


void m_b(Cube3* c){
  short i;

  for (i=0;i<NPC;i++){
    if(c->pc[i].p[0]==-1){
      rot_x(&c->pc[i], 1);
    }
  }
}


/* the layer between L and R, turn direction as L (top-down)*/
void m_M(Cube3* c){
  short i;

  for (i=0;i<NPC;i++){
    if(c->pc[i].p[1]==0){
      rot_y(&c->pc[i], -1);
    }
  }
}

void m_m(Cube3* c){
  short i;

  for (i=0;i<NPC;i++){
    if(c->pc[i].p[1]==0){
      rot_y(&c->pc[i], 1);
    }
  }
}

/* the layer between U and D, turn direction as D (left-right)*/
void m_E(Cube3* c){
  short i;

  for (i=0;i<NPC;i++){
    if(c->pc[i].p[2]==0){
      rot_z(&c->pc[i], -1);
    }
  }
}


void m_e(Cube3* c){
  short i;

  for (i=0;i<NPC;i++){
    if(c->pc[i].p[2]==0){
      rot_z(&c->pc[i], 1);
    }
  }
}

/* the layer between F and B, turn direction as F*/
void m_S(Cube3* c){
  short i;

  for (i=0;i<NPC;i++){
    if(c->pc[i].p[0]==0){
      rot_x(&c->pc[i], 1);
    }
  }
}

void m_s(Cube3* c){
  short i;

  for (i=0;i<NPC;i++){
    if(c->pc[i].p[0]==0){
      rot_x(&c->pc[i], -1);
    }
  }
}



/*the following functions consider different axis than we do in the cube.c for the auxiliary functions. This will be taken into account*/

/* rotate the entire Cube on R*/
void m_X(Cube3* c){
  short i;

  for (i=0;i<NPC;i++){
    rot_y(&c->pc[i], 1);
  }
}

void m_x(Cube3* c){
  short i;

  for (i=0;i<NPC;i++){
    rot_y(&c->pc[i], -1);
  }
}

/* rotate the entire Cube on U*/
void m_Y(Cube3* c){
  short i;

  for (i=0;i<NPC;i++){
    rot_z(&c->pc[i], 1);
  }
}

void m_y(Cube3* c){
  short i;

  for (i=0;i<NPC;i++){
    rot_z(&c->pc[i], -1);
  }
}

/* rotate the entire Cube on F*/
void m_Z(Cube3* c){
  short i;

  for (i=0;i<NPC;i++){
    rot_x(&c->pc[i], 1);
  }
}

void m_z(Cube3* c){
  short i;

  for (i=0;i<NPC;i++){
    rot_x(&c->pc[i], -1);
  }
}



/***********AUXILIARY FUNTIONS***********/



void paint_piece(Piece *pc){
  short aux[3][2]={{G,B},{R,O},{W,Y}},i;

  for(i=0;i<3;i++){
    switch(pc->p[i]){
      case 1:
        pc->c[i]=aux[i][0];
        break;
      case -1:
        pc->c[i]=aux[i][1];
        break;
      default:
        pc->c[i]=N;
    }
  }

}



void assign(short *p, short a, short b, short c){
  p[0]=a;
  p[1]=b;
  p[2]=c;
}


/******PIECE ROTATION********/

void rot_x(Piece *p, short dir){
  short y=p->p[1], z=p->p[2], temp;

  p->p[1]=z*dir;
  p->p[2]=-y*dir;

  temp=p->c[1];
  p->c[1]=p->c[2];
  p->c[2]=temp;
}

void rot_y(Piece *p, short dir){
  short x=p->p[0], z=p->p[2], temp;

  p->p[2]=x*dir;
  p->p[0]=-z*dir;

  temp=p->c[0];
  p->c[0]=p->c[2];
  p->c[2]=temp;
}

void rot_z(Piece *p, short dir){
  short x=p->p[0], y=p->p[1], temp;

  p->p[0]=y*dir;
  p->p[1]=-x*dir;

  temp=p->c[0];
  p->c[0]=p->c[1];
  p->c[1]=temp;
}


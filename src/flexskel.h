/* A lexical scanner header generated by flex */
/* MODIFIED FOR C++ CLASS BY Alain Coetmeur: coetmeur(at)icdc.fr */
/* Note that (at) mean the 'at' symbol that I cannot write */
/* because it is expanded to the class name */
/* made at Informatique-CDC, Research&development department */
/* company from the Caisse Des Depots et Consignations */


/*********************************************/
/* SYSTEM dependent declaration, includes... */
/*********************************************/
#ifdef __cplusplus
#ifndef YY_USE_CLASS
#define YY_USE_CLASS
#endif
#endif
#include <stdio.h>


%% here is the declaration from section1 %header{

#ifdef YY_USE_CLASS
#ifdef YY_@_IOSTREAM
#include <iostream>
#define YY_@_IFILE std::istream
#define YY_@_OFILE std::ostream
#define YY_@_ERRFILE std::cerr

#ifndef YY_@_IFILE_DEFAULT
#define YY_@_IFILE_DEFAULT &std::cin
#endif

#ifndef YY_@_OFILE_DEFAULT
#define YY_@_OFILE_DEFAULT &std::cout
#endif

#endif
#endif

#ifndef YY_@_IFILE
#define YY_@_IFILE FILE
#endif

#ifndef YY_@_OFILE
#define YY_@_OFILE FILE
#endif

#ifndef YY_@_ERRFILE
#define YY_@_ERRFILE stderr
#endif

#ifndef YY_@_IFILE_DEFAULT
#define YY_@_IFILE_DEFAULT stdin
#endif

#ifndef YY_@_OFILE_DEFAULT
#define YY_@_OFILE_DEFAULT stdout
#endif

#ifndef YY_@_TEXT
#define YY_@_TEXT yytext
#endif
#ifndef YY_@_LENG
#define YY_@_LENG yyleng
#endif
#ifndef YY_@_IN
#define YY_@_IN yyin
#endif
#ifndef YY_@_OUT
#define YY_@_OUT yyout
#endif

#ifndef YY_@_LEX_RETURN
#define YY_@_LEX_RETURN int
#else
#ifndef YY_@_LEX_DEFINED
#define YY_@_LEX_DEFINED
#endif
#endif

#ifndef YY_@_LEX
#define YY_@_LEX yylex
#else
#ifndef YY_@_LEX_DEFINED
#define YY_@_LEX_DEFINED
#endif
#endif

#ifndef YY_@_LEX_PARAM
#define YY_@_LEX_PARAM void
#else
#ifndef YY_@_LEX_DEFINED
#define YY_@_LEX_DEFINED
#endif
#endif

#ifndef YY_@_RESTART
#define YY_@_RESTART yyrestart
#endif
#ifndef YY_@_SWITCH_TO_BUFFER
#define YY_@_SWITCH_TO_BUFFER yy_switch_to_buffer
#endif
#ifndef YY_@_LOAD_BUFFER_STATE
#define YY_@_LOAD_BUFFER_STATE yy_load_buffer_state
#endif

#ifndef YY_@_CREATE_BUFFER
#define YY_@_CREATE_BUFFER yy_create_buffer
#ifndef YY_USE_CLASS
#ifndef yy_new_buffer
#define yy_new_buffer yy_create_buffer
#endif
#endif
#endif
#ifndef YY_@_DELETE_BUFFER
#define YY_@_DELETE_BUFFER yy_delete_buffer
#endif
#ifndef YY_@_INIT_BUFFER
#define YY_@_INIT_BUFFER yy_init_buffer
#endif

#ifndef YY_@_DEBUG
#ifdef FLEX_DEBUG
#define YY_@_DEBUG 1
#else
#define YY_@_DEBUG 0
#endif
#endif

#if YY_@_DEBUG != 0
#ifndef YY_@_DEBUG_FLAG
#define YY_@_DEBUG_FLAG yy_flex_debug
#endif
#ifndef YY_@_DEBUG_INIT
#define YY_@_DEBUG_INIT 1
#endif
#endif

#ifndef YY_USE_CLASS
#ifndef YY_@_CURRENT_BUFFER
#define YY_@_CURRENT_BUFFER yy_current_buffer
#endif
typedef struct yy_buffer_state *YY_BUFFER_STATE;

extern void YY_@_RESTART( YY_@_IFILE *input_file );
extern void YY_@_SWITCH_TO_BUFFER( YY_BUFFER_STATE new_buffer );
extern void YY_@_LOAD_BUFFER_STATE( void );
extern YY_BUFFER_STATE YY_@_CREATE_BUFFER( YY_@_IFILE *file, int size );
extern void YY_@_DELETE_BUFFER( YY_BUFFER_STATE b );
extern void YY_@_INIT_BUFFER( YY_BUFFER_STATE b, YY_@_IFILE *file );

#if YY_@_DEBUG != 0
extern int YY_@_DEBUG_FLAG ;
#endif
extern YY_@_CHAR  *YY_@_TEXT;
extern int YY_@_LENG;
extern YY_@_IFILE *YY_@_IN;
extern YY_@_OFILE *YY_@_OUT;
#ifdef YY_@_LEX_DEFINED
extern YY_@_LEX_RETURN YY_@_LEX ( YY_@_LEX_PARAM )
#else
#ifndef YY_DECL
extern YY_@_LEX_RETURN YY_@_LEX ( YY_@_LEX_PARAM )
#else
/* no declaration if oldstyle flex */
#endif
#endif
#else

#ifndef YY_@_CURRENT_BUFFER
#define YY_@_CURRENT_BUFFER YY_CURRENT_BUFFER
#endif
#ifndef YY_@_CLASS
#define YY_@_CLASS @
#endif
#ifndef YY_@_ECHO
#define YY_@_ECHO yy_echo
#endif
#ifdef YY_@_ECHO_PURE
#define YY_@_ECHO_NOCODE
#endif

#ifndef YY_@_ECHO_CODE
#ifndef YY_@_IOSTREAM
#define YY_@_ECHO_CODE fwrite( (char *) YY_@_TEXT, YY_@_LENG, 1, YY_@_OUT );
#else
#define YY_@_ECHO_CODE (YY_@_OUT->write( (char *) YY_@_TEXT, YY_@_LENG));
#endif
#endif

#ifndef YY_@_INPUT
#define YY_@_INPUT yy_input
#endif
#ifdef YY_@_INPUT_PURE
#define YY_@_INPUT_NOCODE
#endif

#ifndef YY_@_INPUT_CODE
#ifndef YY_@_IOSTREAM
#define YY_@_INPUT_CODE return result= fread(  buffer, 1,max_size,YY_@_IN );
#else
#define YY_@_INPUT_CODE if(YY_@_IN->eof())  result=0;else {YY_@_IN->read(buffer,max_size);result=YY_@_IN->gcount();YY_@_IN->clear(YY_@_IN->rdstate()&(~std::ios::failbit));if(YY_@_IN->bad()) result= -1;} return result;
#endif
#endif

#ifdef YY_@_FATAL_ERROR_PURE
#define YY_@_FATAL_ERROR_NOCODE
#endif
#ifndef YY_@_FATAL_ERROR
#define YY_@_FATAL_ERROR yy_fatal_error
#endif

#ifndef YY_@_FATAL_ERROR_CODE
#ifndef YY_@_IOSTREAM
#define YY_@_FATAL_ERROR_CODE fputs( msg, YY_@_ERRFILE );putc( '\n', YY_@_ERRFILE );exit( 1 );
#else
#define YY_@_FATAL_ERROR_CODE YY_@_ERRFILE<< msg <<std::endl;exit( 1 );
#endif
#endif

#ifndef YY_@_WRAP
#define YY_@_WRAP yy_wrap
#endif
#ifdef YY_@_WRAP_PURE
#define YY_@_WRAP_NOCODE
#endif
#ifndef YY_@_WRAP_CODE
#define YY_@_WRAP_CODE return 1;
#endif

#ifndef YY_@_INHERIT
#define YY_@_INHERIT
#endif
#ifndef YY_@_MEMBERS
#define YY_@_MEMBERS
#endif
#ifndef YY_@_CONSTRUCTOR_PARAM
#define YY_@_CONSTRUCTOR_PARAM
#endif
#ifndef YY_@_CONSTRUCTOR_CODE
#define YY_@_CONSTRUCTOR_CODE
#endif
#ifndef YY_@_CONSTRUCTOR_INIT
#define YY_@_CONSTRUCTOR_INIT
#endif
#ifndef YY_@_DESTRUCTOR_CODE
#define YY_@_DESTRUCTOR_CODE
#endif
typedef struct yy_buffer_state *YY_BUFFER_STATE;

class YY_@_CLASS YY_@_INHERIT
{
 private:/* data */
 YY_@_CHAR  *yy_c_buf_p;
 YY_@_CHAR  yy_hold_char;
 int yy_n_chars;
 int yy_init;
 int yy_start;
 int yy_did_buffer_switch_on_eof;
 private: /* functions */
 void yy_initialize();
 int input();
 int yyinput() {return input();};
 int yy_get_next_buffer();
 void yyunput( YY_@_CHAR  c, YY_@_CHAR  *buf_ptr );
 /* use long instead of yy_state_type because it is undef */
 long yy_get_previous_state_();
 long yy_try_NUL_trans_  ( long current_state_ );
 protected:/* non virtual */
 YY_BUFFER_STATE YY_@_CURRENT_BUFFER;
 void YY_@_RESTART ( YY_@_IFILE *input_file );
 void YY_@_SWITCH_TO_BUFFER( YY_BUFFER_STATE new_buffer );
 void YY_@_LOAD_BUFFER_STATE( void );
 YY_BUFFER_STATE YY_@_CREATE_BUFFER( YY_@_IFILE *file, int size );
 void YY_@_DELETE_BUFFER( YY_BUFFER_STATE b );
 void YY_@_INIT_BUFFER( YY_BUFFER_STATE b, YY_@_IFILE *file );
 protected: /* virtual */
 virtual void YY_@_ECHO()
#ifdef YY_@_ECHO_PURE
  =0
#endif
  ;
 virtual int  YY_@_INPUT(char  *buf,int &result,int max_size)
#ifdef YY_@_INPUT_PURE
  =0
#endif
  ;
 virtual void  YY_@_FATAL_ERROR(const char *msg)
#ifdef YY_@_FATAL_ERROR_PURE
  =0
#endif
  ;
 virtual int  YY_@_WRAP()
#ifdef YY_@_WRAP_PURE
  =0
#endif
  ;
 public:
 YY_@_CHAR  *YY_@_TEXT;
 int YY_@_LENG;
 YY_@_IFILE *YY_@_IN;
 YY_@_OFILE *YY_@_OUT;
 YY_@_LEX_RETURN YY_@_LEX ( YY_@_LEX_PARAM);
 YY_@_CLASS(YY_@_CONSTRUCTOR_PARAM) ;
 virtual ~YY_@_CLASS() ;
#if YY_@_DEBUG != 0
 int YY_@_DEBUG_FLAG;
#endif
 public: /* added members */
 YY_@_MEMBERS
};
#endif



/* declaration of externs for public use of yylex scanner */

%% here is the declaration from section2 %header{

/* end of generated header */

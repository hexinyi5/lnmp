#define printDBL( exp ) printf( #exp " = %f ", exp )
printDBL( 4 * atan(1.0) );

#define showArgs(...) puts(#__VA_ARGS__)
showArgs( one\n,            "2\n", three);

#define printLog(...) fprintf( fp_log, __VA_ARGS__ )
printLog("%s: intVar = %d\n", __func__, intVar );


#define DISTANCE(x, y) ((x)>=(y)? (x)-(y): (y)-(x))
d = DISTANCE(a, b-0.5);

#define TEXT_A "Hello, world!"
#define msg(x) puts( TEXT_ ## x)
msg()

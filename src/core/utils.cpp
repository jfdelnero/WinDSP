
short CheckOverflow( int samplevalue )
{
	if( samplevalue > 32767 )
		return 32767;
		
	if( samplevalue < -32768 )
		return -32768;
		
	return samplevalue;
}
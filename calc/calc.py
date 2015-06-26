
import math
import numpy

def readData():
    inFile = "volt.txt"
    inData = []
    outData = []
    with open( inFile ) as f:
        for line in f:
            #print line
            line = line.split() # to deal with blank 
            if line:            # lines (ie skip them)
                l = [float(i) for i in line]
                #print "data: {1}".format( l )
                inData.append( [ unifyX(l[0]), unifyX( l[1] ) ] )
                outData.append( [ unifyY( l[4] ) ] )
    return ( inData, outData )
    
def unifyX( x ):
    res = (x-2047.0) / 2048.0
    return res
    
def unifyY( y ):
    res = y / 10000.0
    return res
    
def restoreX( x ):
    res = x *2048.0 + 2047.0
    return res
    
def restoreY( y ):
    res = y * 10000.0
    return res
    
def linReg( x, y, wd=True, k=0.0 ):
    X_ = []
    Y_ = []
    #print x
    sz = len(x)
    for i in range( sz ):
        #print x[i][0]
        #print x[i][1]
        #print x[i][2]
        xx = zLine( x[i] )
        X_.append( xx )
        Y_.append( y[i] )
    Y = numpy.matrix( Y_ )
    X = numpy.matrix( X_ )
    
    XT = X.transpose()
    # Calc XTX
    XTX = XT * X

    # Lambda.
    if ( wd ):
        lmbd = math.pow( 10.0, k )
        sz = len( X_[0] )
        L = numpy.identity( sz ) * lmbd
        #print "lambda = ", lmbd
        XTX = XTX + L
    
    #Calc XTY
    XTY = XT * Y
    
    # Invert xTx
    invXTX = numpy.linalg.matrix_power( XTX, -1 )
    
    # Multiply W = invXTX * XTY
    W = invXTX * XTY

    #print "W = "
    #print W
    w = []
    sz = len( X_[0] )
    for i in range( sz ):
        w.append( W[i, 0] )
    return w
    
def zLine( x ):
    #z = [ 1, x[0], x[0]*x[0], x[0]*x[0]*x[0], x[1], x[1]*x[1], x[1]*x[1]*x[1] ]
    z = [ 1, x[0], x[1] ]
    return z
    
def func( w, x ):
    xx = zLine( x )
    sz = len( xx )
    y = 0.0
    for i in xrange( sz ):
        www = w[i]
        xxx = xx[i]
        a = www * xxx
        y += a
    return y
    
def Eout( w, inData, outData, outInd1, outInd2 ):
    xOut = []
    yOut = []
    sz = len( inData )
    for i in range( outInd1, outInd2 ):
        xOut.append( inData[i] )
        yOut.append( outData[i] )
    
    Eo = 0.0
    sz = len( xOut )
    for i in xrange( sz ):
        y = func( w, xOut[i] )
        y -= yOut[i][0]
        Eo = Eo + (y*y)
    Eo = math.sqrt( Eo ) / float( sz )
    return Eo

def EoutMean( cnt = 5, wd = False, k = -10.0 ):
    inData, outData = readData()
    dataSz = len( inData )
    EoutRes = 0.0
    for ii in range( 0, cnt ):
        iFrom  = dataSz/5*ii
        iTo    = dataSz/5*(ii+1)
        checkRange = range( iFrom, iTo )
        inDataTr  = []
        outDataTr = []
        inDataCh  = []
        outDataCh = []
        for i in xrange(dataSz):
            if ( i not in checkRange ):
                inDataTr.append( inData[i] )
                outDataTr.append( outData[i] )
        w = linReg( inDataTr, outDataTr, wd, k )
        Eo = Eout( w, inData, outData, iFrom, iTo )
        EoutRes += Eo
    EoutRes /= float( cnt )
    EoutRes = restoreY( EoutRes )
    w = linReg( inData, outData, wd, k )
    return ( EoutRes, w )
    
e, w = EoutMean()
print "Eout(as is)       = {:.10f} [mV]".format( e ) 
print w
        
e, w = EoutMean( 5, True, -3.65 )
print "Eout(constrained) = {:.10f} [mV]".format( e ) 
print w

    

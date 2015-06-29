
function cb( a, b, c )
  --print( a )
end

function cbFull( a, b, c )
  if ( #a > 0 ) then
    print( a[1] )
  end
end

voltamp.dataCallbackRegister( cb )
voltamp.dataCallbackRegisterFull( cbFull )

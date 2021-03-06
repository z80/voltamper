setwd("~/projects/voltamper.git/calc")
d = read.table( "./volt.txt" )
names( d )[1] <- "dac0"
names( d )[2] <- "dac1"
names( d )[3] <- "ref"
names( d )[4] <- "aux"
names( d )[5] <- "v"
d$rr <- as.numeric(d$ref) * as.numeric(d$ref)

summary( d )
#c = cov( d )
model <- lm( v ~ ref, data = d )
summary( model )$sigma

newd = data.frame( ref = d$ref )

data <- predict( model, newd )
#library( ridge )
plot( d$ref, d$v - data )

coef( model )

#linearRidge( formula, d )
library( lasso2 )
lm = l1ce( v ~ ref + rr, data = d, bound = 0.99999999 )
summary(lm)$sigma
summary(lm)$coef

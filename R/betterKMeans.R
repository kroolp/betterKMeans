kmeans <- function(pointsMatrix, k, epsilon, maxIter) {
  result <- KM::kMeans(pointsMatrix, k, epsilon, maxIter);

  plot(pointsMatrix, col=result$labels, cex=.1, pch=19, xlab="X", ylab="Y");
  points(result$centers, col=c(1:k), cex=.4, pch=19);
  text(result$centers, col=c(1:k), labels=c(1:k), cex=.8, pos=4);
}

kOmeans <- function(pointsMatrix, k, epsilon, maxIter, omega) {
  result <- KM::kOMeans(pointsMatrix, k, epsilon, maxIter, omega);
  
  plot(pointsMatrix, col=result$labels, cex=.1, pch=19, xlab="X", ylab="Y");
  points(result$centers, col=c(1:k), cex=.4, pch=19);
  text(result$centers, col=c(1:k), labels=c(1:k), cex=.8, pos=4);
  
  for(i in 1:k)
  {
    base <- result$bases[,,k];
    polypnts <- cbind(x=c(base[1,1], result$centers[i,1], base[1,2]), y=c(base[2,1], result$centers[i,2], base[2,2]))
    polygon(polypnts, col=adjustcolor(i, alpha.f=0.2), border=NA);
  }
}
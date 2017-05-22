plot_kMeans <- function(pointsMatrix, k, epsilon, maxIter) {
  result <- KM::kMeans(pointsMatrix, k, epsilon, maxIter);

  plot_points(pointsMatrix, result$labels);
  draw_centers(result$centers, k);
}

plot_kOMeans <- function(pointsMatrix, k, epsilon, maxIter, omega) {
  result <- KM::kOMeans(pointsMatrix, k, epsilon, maxIter, omega);
  
  plot_points(pointsMatrix, result$labels);
  draw_centers(result$centers, k);
  draw_bases(result$bases, result$centers, k);
}

plot_betterKMeans <- function(pointsMatrix, k, epsilon, maxIter, omega, expression, pointsToPlot) {
  result <- KM::betterKMeans(pointsMatrix, k, epsilon, maxIter, omega, expression, pointsToPlot);
  
  plot_points(pointsMatrix, result$labels);
  draw_centers(result$centers, k);
  draw_bases(result$eigenVectors, result$eigenValues, result$centers, k);
  draw_functions(result$pointsToDraw, k);
}

plot_points <- function(pointsMatrix, labels) {
  plot(pointsMatrix, col=labels, cex=.1, pch=19, xlab="X", ylab="Y", asp=1, xlim=c(0, 1.0), ylim=c(0, 1.0));
}

draw_centers <- function(centers, k) {
  points(centers, col=c(1:k), cex=.4, pch=19);
  text(centers, col=c(1:k), labels=c(1:k), cex=.8, pos=4);
}

draw_bases <- function(eigenVectors, eigenValues, centers, k) {
  for(i in 1:k)
  {
    eigenVector <- eigenVectors[,,k];
    xpoints = c(2*sqrt(eigenValues[1,1,k]) * eigenVector[1,1] + centers[i,1], centers[i,1], 2*sqrt(eigenValues[1,1,k]) *eigenVector[1,2] + centers[i,1]);
    ypoints = c(2*sqrt(eigenValues[2,1,k]) *eigenVector[2,1] + centers[i,2], centers[i,2], 2*sqrt(eigenValues[2,1,k]) *eigenVector[2,2] + centers[i,2]);

    polypnts <- cbind(x=xpoints, y=ypoints)
    polygon(polypnts, col=adjustcolor(i, alpha.f=0.2), border=NA);
  }
}

draw_functions <- function(pointsToDraw, k) {
  for(i in 1:k)
  {
    lines(list(x=pointsToDraw[,1,i], y=pointsToDraw[,2,i]), col=i);
  }
}
kmeans <- function(pointsMatrix, k, epsilon, maxIter) {
  result <- KM::kMeans(pointsMatrix, k, epsilon, maxIter);

  plot(pointsMatrix, col=result$labels, cex=.1, pch=19, xlab="X", ylab="Y");
  points(result$centers, col=c(1:k), cex=.4, pch=19);
  text(result$centers, col=c(1:k), labels=c(1:k), cex=.8, pos=4);
}
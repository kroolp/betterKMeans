plot.kmeans <- function(result, cex=.1, pch=19, xlab="X", ylab="Y", asp=1, xlim=c(0, 1.0), ylim=c(0, 1.0), type=NULL, main=NULL, sub=NULL) {
  k = length(result$errors);

  plot_points(result$inputMatrix, result$labels, cex=cex, pch=pch, xlab=xlab, ylab=ylab, asp=asp, xlim=xlim, ylim=ylim, type=type, main=main, sub=sub);
  draw_centers(result$centers, k);
}

plot.kOmeans <- function(result, cex=.1, pch=19, xlab="X", ylab="Y", asp=1, xlim=c(0, 1.0), ylim=c(0, 1.0), type=NULL, main=NULL, sub=NULL) {
  k = length(result$errors);
  
  plot_points(result$inputMatrix, result$labels, cex=cex, pch=pch, xlab=xlab, ylab=ylab, asp=asp, xlim=xlim, ylim=ylim, type=type, main=main, sub=sub);
  draw_centers(result$centers, k);
  
  draw_bases(result$eigenVectors, result$eigenValues, result$centers, k);
  abline(0,0);
}

plot.betterKmeans <- function(result, cex=.1, pch=19, xlab="X", ylab="Y", asp=1, xlim=c(0, 1.0), ylim=c(0, 1.0), type=NULL, main=NULL, sub=NULL) {
  k = length(result$errors);
  
  plot_points(result$inputMatrix, result$labels, cex=cex, pch=pch, xlab=xlab, ylab=ylab, asp=asp, xlim=xlim, ylim=ylim, type=type, main=main, sub=sub);
  draw_centers(result$centers, k);

  draw_bases(result$eigenVectors, result$eigenValues, result$centers, k);
  draw_functions(result$pointsToDraw, k);
}

plot_result <- function(result, cex=.1, pch=19, xlab="X", ylab="Y", asp=1, xlim=c(0, 1.0), ylim=c(0, 1.0), type=NULL, main=NULL, sub=NULL) {
  k = length(result$errors);
  
  plot_points(result$inputMatrix, result$labels, cex=cex, pch=pch, xlab=xlab, ylab=ylab, asp=asp, xlim=xlim, ylim=ylim, type=type, main=main, sub=sub);
  draw_centers(result$centers, k);
  
  if(!is.null(result$eigenVectors))
    draw_bases(result$eigenVectors, result$eigenValues, result$centers, k);
  
  if(!is.null(result$pointsToDraw))
    draw_functions(result$pointsToDraw, k);
  
  if(!is.null(result$eigenVectors) && is.null(result$pointsToDraw))
    abline(0,0);
}

plot.kmeans <- plot.kOmeans <- plot.betterKmeans <- plot_result;

plot_points <- function(pointsMatrix, labels, cex, pch, xlab, ylab, asp, xlim, ylim, type, main, sub) {
  plot(pointsMatrix, col=labels, cex=cex, pch=pch, xlab=xlab, ylab=ylab, asp=asp, xlim=xlim, ylim=ylim, type=type, main=main, sub=sub);
}

draw_centers <- function(centers, k) {
  points(centers, col=c(1:k), cex=.4, pch=19);
  text(centers, col=c(1:k), labels=c(1:k), cex=.8, pos=4);
}

draw_bases <- function(eigenVectors, eigenValues, centers, k) {
  for(i in 1:k)
  {
    eigenVector <- eigenVectors[,,k];
    xpoints = c(2*sqrt(eigenValues[1,1,k]) * eigenVector[1,1] + centers[i,1], centers[i,1], 2*sqrt(eigenValues[2,1,k]) *eigenVector[1,2] + centers[i,1]);
    ypoints = c(2*sqrt(eigenValues[1,1,k]) *eigenVector[2,1] + centers[i,2], centers[i,2], 2*sqrt(eigenValues[2,1,k]) *eigenVector[2,2] + centers[i,2]);

    polypnts <- cbind(x=xpoints, y=ypoints)
    polygon(polypnts, col=adjustcolor(i, alpha.f=0.2), border=NA);
  }
}

draw_functions <- function(pointsToDraw, k) {
  for(i in 1:k)
    lines(list(x=pointsToDraw[,1,i], y=pointsToDraw[,2,i]), col=i);
}
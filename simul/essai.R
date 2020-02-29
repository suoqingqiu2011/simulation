g = read.table("result")
jpeg("hist.jpg")
hist(g$V1, breaks = 10)
dev.off()


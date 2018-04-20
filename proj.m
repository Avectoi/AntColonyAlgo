clear all
close all
clc
load map1691.mat
N = size(outmap,2);
iter = size(outmap,1)/N;
outmap = reshape(outmap,iter,N,N);
for i = 1:iter
    o = squeeze(outmap(i,:,:));
    m = min(o(:));
    mm = max(o(:));
    outmap(i,:,:) = (o-m)/(mm-m);
end
outmap(isnan(outmap))=0;
v = VideoWriter('ant.avi');
open(v)
for it = 1:iter
    if 0==0
    scatter(location(1:N,1),location(1:N,2));
    hold on
    for i = 1:N
        for j = i+1:N
            x = [location(i,1),location(j,1)];
            y = [location(i,2),location(j,2)];
            color = 1/(1+max(outmap(it,j,i),outmap(it,i,j)));
            plot(x,y,'color',[1,color,color]);
        end
    end
    for i = 1:N
        text(location(i,1),location(i,2)-5,name{i})
    end
    scatter(location(1:N,1),location(1:N,2),'b','filled');
    hold off
    pause(0.001)
    F = getframe(gcf);
    %for k = 1:10
    writeVideo(v,F);
    %end
    end
end
close(v);
v = VideoWriter('ant1.avi');
open(v)
t_ = size(route,1);
for i = 1:t_
hold off
scatter(location(1:N,1),location(1:N,2),'b','filled');
hold on
x = location(route(i,:),1);
y = location(route(i,:),2);
plot(x,y,'b')
for j = 1:N
    text(location(j,1),location(j,2)-5,name{j})
end
pause(0.01)
F = getframe(gcf);
    for k = 1:10
        writeVideo(v,F);
    end
end
close(v);

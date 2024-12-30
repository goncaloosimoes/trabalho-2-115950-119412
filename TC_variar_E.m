metrics = [0.000030	       0.000010	           1373	              0	              0	              0	              0	            225	           1320;
            0.000154	       0.000051	          15143	           1500	            210	             70	             70	            225	           6088;
            0.000680	       0.000226	          61934	           7684	            654	            210	            210	            225	          22038;
            0.000782	       0.000260	          86984	          11785	            702	            210	            210	            225	          30392;
            0.000787	       0.000262	         112807	          16044	            735	            210	            210	            225	          39000;
            0.001338	       0.000444	         137411	          20134	            708	            210	            210	            225	          47220;
            0.001223	       0.000406	         162144	          24260	            672	            210	            210	            225	          55482;
            0.001358	       0.000451	         186869	          28377	            663	            210	            210	            225	          63730;
            0.001285	       0.000427	         211240	          32444	            636	            210	            210	            225	          71866;
            0.001255	       0.000417	         235666	          36513	            630	            210	            210	            225	          80012;
            0.001265	       0.000420	         260061	          40578	            630	            210	            210	            225	          88144;
            0.001493	       0.000496	         272378	          42630	            630	            210	            210	            225	          92250];



numVertices = 15;
numEdges = [0 20 40 60 80 100 120 140 160 180 200 210];

MEMOPS = metrics(:, 3);
DIST_COMPS = metrics(:, 4);
UPDATES = metrics(:, 5);
ADDED_EDGES = metrics(:, 6);
REACHED_VERTICES = metrics(:, 7);
REACHED_CHECKS = metrics(:, 8);
COMPS = metrics(:, 9);


figure;
hold on;
plot(numEdges, MEMOPS, '-o', 'LineWidth', 1, 'DisplayName', 'MEMOPS');
plot(numEdges, COMPS, '-o', 'LineWidth', 1, 'DisplayName', 'COMPS');
plot(numEdges, DIST_COMPS, '-o', 'LineWidth', 1, 'DisplayName', 'DIST COMPS');
xlabel('Número de Arestas (E)');
ylabel('Valor das Métricas');
title('Comparação de Métricas vs Número de Arestas (Nº vértices = 15)');
legend('Location', 'best');
grid on;
hold off; 

figure;
hold on;
plot(numEdges, UPDATES, '-o', 'LineWidth', 1, 'DisplayName', 'UPDATES');
plot(numEdges, ADDED_EDGES, '-o', 'LineWidth', 1, 'DisplayName', 'ADDED EDGES');
plot(numEdges, REACHED_VERTICES, '-o', 'LineWidth', 1, 'DisplayName', 'REACHED VERTICES');
plot(numEdges, REACHED_CHECKS, '-o', 'LineWidth', 1, 'DisplayName', 'REACHED CHECKS');
xlabel('Número de Arestas (E)');
ylabel('Valor das Métricas');
title('Comparação de Métricas vs Número de Arestas (Nº vértices = 15)');
legend('Location', 'best');
grid on;
hold off; 


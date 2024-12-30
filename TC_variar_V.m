clear;clc;
metrics = [
            0.000047	       0.000036	          13468	           1582	            225	             73	             73	            100	           4938;
            0.000124	       0.000097	          30633	           2345	            231	             77	             77	            900	          14326;
            0.000225	       0.000176	          36550	           1947	            120	             40	             40	           2500	          22638;
            0.000487	       0.000380	          59815	           2747	            120	             40	             40	           4900	          40216;
            0.000802	       0.000625	          80074	           2846	             96	             32	             32	           8100	          59768;
            0.001324	       0.001033	         109934	           3376	             93	             31	             31	          12100	          85854;
            0.002026	       0.001581	         149807	           4379	            102	             34	             34	          16900	         118628;
            0.002977	       0.002323	         187626	           4763	             96	             32	             32	          22500	         153718;
            0.004014	       0.003132	         227562	           4899	             87	             29	             29	          28900	         192636;
            0.005381	       0.004198	         279215	           5667	             90	             30	             30	          36100	         238860
            ];


numVertices = [10 30 50 70 90 110 130 150 170 190];
numArestas = 25;

MEMOPS = metrics(:, 3);
DIST_COMPS = metrics(:, 4);
UPDATES = metrics(:, 5);
ADDED_EDGES = metrics(:, 6);
REACHED_VERTICES = metrics(:, 7);
REACHED_CHECKS = metrics(:, 8);
COMPS = metrics(:, 9);

figure;
hold on;
plot(numVertices, MEMOPS, '-o', 'LineWidth', 1, 'DisplayName', 'MEMOPS');
plot(numVertices, COMPS, '-o', 'LineWidth', 1, 'DisplayName', 'COMPS');
plot(numVertices, DIST_COMPS, '-o', 'LineWidth', 1, 'DisplayName', 'DIST COMPS');
xlabel('Número de Vértices (V)');
ylabel('Valor das Métricas');
title('Comparação de Métricas vs Número de Vértices (Nº arestas = 25)');
legend('Location', 'best');
grid on;
hold off; 

figure;
hold on;
plot(numVertices, UPDATES, '-o', 'LineWidth', 1, 'DisplayName', 'UPDATES');
plot(numVertices, ADDED_EDGES, '-o', 'LineWidth', 1, 'DisplayName', 'ADDED EDGES');
plot(numVertices, REACHED_VERTICES, '-o', 'LineWidth', 1, 'DisplayName', 'REACHED VERTICES');
plot(numVertices, REACHED_CHECKS, '-o', 'LineWidth', 1, 'DisplayName', 'REACHED CHECKS');
xlabel('Número de Vértices (V)');
ylabel('Valor das Métricas');
title('Comparação de Métricas vs Número de Vértices (Nº arestas = 25)');
legend('Location', 'best');
grid on;
hold off; 
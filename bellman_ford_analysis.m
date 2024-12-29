metrics_d0 = [
                0.000006	       0.000002	             84	              5	              3;
                0.000005	       0.000001	            143	             10	              6;
                0.000004	       0.000001	            175	             13	              9;
                0.000002	       0.000001	             25	              0	              0;
                0.000002	       0.000000	             25	              0	              0;
                0.000004	       0.000001	            196	             15	             12
                ];

metrics_d1 = [
                0.000006	       0.000002	            470	             50	             15;
                0.000003	       0.000001	            203	             20	              6;
                0.000003	       0.000001	            175	             17	              6;
                0.000099	       0.000029	            408	             43	             15;
                0.000006	       0.000002	            223	             21	              9;
                0.000003	       0.000001	            158	             15	              6
                ];

metrics_d2 = [
                0.000006	       0.000002	            590	             71	             18;
                0.000005	       0.000002	            528	             63	             15;
                0.000005	       0.000001	            540	             65	             15;
                0.000005	       0.000001	            529	             64	             15;
                0.000004	       0.000001	            506	             61	             15;
                0.000005	       0.000001	            518	             63	             15
                ];

metrics_d3 = [
                0.000009	       0.000003	            770	            100	             15;
                0.000006	       0.000002	            741	             96	             15;
                0.000005	       0.000001	            718	             93	             15;
                0.000005	       0.000001	            631	             81	             15;
                0.000005	       0.000001	            678	             88	             15;
                0.000005	       0.000001	            620	             80	             15
                ];

metrics_d4 = [
                0.000010	       0.000003	            920	            125	             15;
                0.000007	       0.000002	            850	            115	             15;
                0.000018	       0.000005	            862	            117	             15;
                0.000005	       0.000002	            827	            112	             15;
                0.000005	       0.000001	            757	            102	             15;
                0.000005	       0.000001	            775	            105	             15
                ];

metrics_d5 = [
                0.000006	       0.000002	           1070	            150	             15;
                0.000006	       0.000002	           1035	            145	             15;
                0.000005	       0.000002	           1000	            140	             15;
                0.000005	       0.000001	            965	            135	             15;
                0.000005	       0.000002	            930	            130	             15;
                0.000009	       0.000003	            895	            125	             15
                ];


%%

medias_d0 = mean(metrics_d0);
medias_d1 = mean(metrics_d1);
medias_d2 = mean(metrics_d2);
medias_d3 = mean(metrics_d3);
medias_d4 = mean(metrics_d4);
medias_d5 = mean(metrics_d5);
%%

numArestas = [5 10 15 20 25 30];
numVertices = 6;
medias = [medias_d0; medias_d1; medias_d2; medias_d3; medias_d4; medias_d5];

MEMOPS = medias(:, 3);
DIST_COMPS = medias(:, 4);
UPDATES = medias(:, 5);
TIME = medias(:, 1);

metricas = [MEMOPS, DIST_COMPS, UPDATES];

figure;
bar(numArestas, metricas, 'grouped');

xlabel('Número de Arestas');
ylabel('Valor Médio');      
title('Comparação de Médias Entre Métricas');
legend({'MEMOPS', 'DISTCOMPS', 'UPDATES'}, 'Location', 'northwest');
grid on;

%Gráfico do tempo

figure;
plot(numArestas, TIME, '-o', 'LineWidth', 1, 'DisplayName', 'TIME');
xlabel('Número de Arestas (E)');
ylabel('Tempo (s)');
title('Tempo vs Número de Arestas');
legend('Location','best');
grid on;

%%

figure;
hold on; 

plot(numArestas, MEMOPS, '-o', 'LineWidth', 1, 'DisplayName', 'MEMOPS');
plot(numArestas, DIST_COMPS, '-s', 'LineWidth', 1, 'DisplayName', 'DISTCOMPS');
plot(numArestas, UPDATES, '-^', 'LineWidth', 1, 'DisplayName', 'UPDATES');

xlabel('Número de Arestas (E)');
ylabel('Valor das Métricas');
title('Comparação de Métricas vs Número de Arestas');
legend('Location', 'best');
grid on;
hold off; 


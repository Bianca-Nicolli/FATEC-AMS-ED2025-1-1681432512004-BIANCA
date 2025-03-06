#include <stdio.h>

void aplicarDesconto(float *preco, float desconto) {
*preco -= (*preco * (desconto / 100));
}
 
int main () {
float preco, desconto, descontoAplicado;

printf("Digite o preço do produto: ");
scanf ("%f", &preco);

printf("Digite o percentual de desconto: ");
scanf ("%f", &desconto);

printf("Preco original: R$ %.2f\n", preco);

descontoAplicado = preco * (desconto / 100);
aplicarDesconto (&preco, desconto);

printf("Desconto Aplicado: R$ %.2f (%.2f%%)\n", descontoAplicado, desconto);
printf("preco final: R$ %.2f\n", preco);
return 0;
}
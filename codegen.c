#include "9cc.h"

void gen_lval(Node *node) {
    if (node->kind != ND_LVAR)
        error("left-hand side of assignment is not a variable");

    printf("  mov rax, rbp\n");
    printf("  sub rax, %d\n", node->offset);
    printf("  push rax\n");
}
void gen(Node *node) {
    switch (node->kind) {
        case ND_NUM:
            printf("  push %d\n", node->val);
            return;
        case ND_LVAR:
            gen_lval(node);
            printf("  pop rax\n");
            printf("  mov rax, [rax]\n");
            printf("  push rax\n");
            return;
        case ND_ASS:
            gen_lval(node->lhs);
            gen(node->rhs);

            printf("  pop rdi\n");
            printf("  pop rax\n");
            printf("  mov [rax], rdi\n");
            printf("  push rdi\n");
            return;
    }

    gen(node->lhs);
    gen(node->rhs);

    printf("  pop rdi\n");
    printf("  pop rax\n");

    switch (node->kind) {
        case ND_ADD:
            printf("  add rax, rdi\n");
            printf("  push rax\n");
            break;
        case ND_SUB:
            printf("  sub rax, rdi\n");
            printf("  push rax\n");
            break;
        case ND_MUL:
            printf("  imul rax, rdi\n");
            printf("  push rax\n");
            break;
        case ND_DIV:
            printf("  cqo\n");
            printf("  idiv rdi\n");
            printf("  push rax\n");
            break;
        case ND_E:
            printf("  cmp rax, rdi\n");
            printf("  sete al\n");
            printf("  movzb rax, al");
            break;
        case ND_NE:
            printf("  cmp rax, rdi\n");
            printf("  setne al\n");
            printf("  movzb rax, al");
            break;
        case ND_L:
            printf("  cmp rax, rdi\n");
            printf("  setl al\n");
            printf("  movzb rax, al");
            break;
        case ND_LE:
            printf("  cmp rax, rdi\n");
            printf("  setle al\n");
            printf("  movzb rax, al");
            break;
        case ND_G:
            printf("  cmp rdi, rax\n");
            printf("  setl al\n");
            printf("  movzb rax, al");
            break;
        case ND_GE:
            printf("  cmp rdi, rax\n");
            printf("  setle al\n");
            printf("  movzb rax, al");
    }
} // TODO optimize
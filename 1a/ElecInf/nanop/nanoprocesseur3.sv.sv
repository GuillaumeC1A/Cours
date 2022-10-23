`default_nettype none
/////////////////////////////////////////////////////////////////////////////////////
// Code pour le test du Nanoprocesseur : ETAPE3
/////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////
// Module auxiliaire pour les registres
/////////////////////////////////////////////////////////////////////////////////////
// Un module permettant de stocker une donnée de 'width' bits conditionnellement a un signal de chargement.
module registre #(parameter width=4) (input logic clk, input logic [width-1:0]D, input logic LOAD, output logic [width-1:0]Q) ;
  always @(posedge clk) if(LOAD) Q <= D ;
endmodule


////////////////////////////////////////////////////////////////////////////////////////////
// Le nanoprocesseur proprement dit
////////////////////////////////////////////////////////////////////////////////////////////

module processeur(input logic clk,
                  input logic reset_n,
                  output logic WRITE,
                  output logic [7:0] ADDR,
                  output logic [7:0] DOUT,
                  input logic [7:0] DIN) ;

// Registre d'addresse
// La donnée provenant de la mémoire est stockée dans cette mémoire (si c'est une addresse)
  logic Load_Addr ;
  logic [7:0] Addr_out;
  registre #(.width(8))  reg_Addr(.clk(clk), .D(DIN), .Q(Addr_out), .LOAD(Load_Addr)) ;


// Multiplexeur d'addresses
// L'addresse en sortie (ADDR) provient soit du PC soit du registre d'adresse
  logic Sel_Addr;
  logic [7:0] PC_out ;
  always @( *)
      ADDR <= Sel_Addr ? Addr_out : PC_out ;

  // PC
  // Le PC n'est plus directement connecté a l'adresse de sortie (ADDR)
  logic Inc_PC ;
  PC u_PC(.clk(clk), .reset_n(reset_n), .Inc_PC(Inc_PC),  .PC(PC_out)) ;

  // Registre d'instruction
  logic Load_I ;
  logic [7:0] I;
  registre #(.width(8))  reg_I(.clk(clk), .D(DIN), .Q(I), .LOAD(Load_I)) ;

  // Le multiplexeur a l'entrée du registre accumulateur
  // on choisit entre la donnée en provenance de la mémoire
  // et la sortie de l'ALU
  logic Sel_Acc ;
  logic [7:0] Acc_in;
  logic[7:0] ALU_out ;
  always @( *)
      Acc_in <= Sel_Acc ? DIN : ALU_out ;

  // Registre d'accumulation
  // La sortie vers la mémoire provient maintenant de l'accumulateur
  logic Load_Acc ;
  registre #(.width(8))  reg_Acc(.clk(clk), .D(Acc_in), .Q(DOUT), .LOAD(Load_Acc)) ;

  // Unité arithmétique et logique
  // Sa sortie n'est plus directement connectée a la mémoire
  ALU u_ALU(.I(I),
            .Op1(DOUT),
            .Op2(DIN),
            .ALU_out(ALU_out)) ;

  // Controleur
  // 3 nouveaux signaux de contrôle à générer
  CTRL u_CTRL(.clk(clk),
              .reset_n(reset_n),
              .I(I),
              .Load_I(Load_I),
              .Load_Acc(Load_Acc),
              .Sel_Acc(Sel_Acc),
              .Load_Addr(Load_Addr),
              .Sel_Addr(Sel_Addr),
              .Inc_PC(Inc_PC),
              .WRITE(WRITE));


endmodule

////////////////////////////////////////////////////////////////////////////////////////////
// L'assemblage du micro processeur avec sa mémoire associée
// Une barre de LED en sortie pour un usage futur..
////////////////////////////////////////////////////////////////////////////////////////////
module board(input logic clk,
             input logic reset_n,
             output logic [7:0] LedBar) ;

  // Les signaux de connection
  logic [7:0] RAM_ADDR ;
  logic [7:0] RAM_DIN ;
  logic [7:0] RAM_DOUT ;
  logic RAM_WRITE ;

  // L'instance de  la mémoire
  ram u_ram(.clk(clk), .ADDR(RAM_ADDR), .D(RAM_DIN), .Q(RAM_DOUT), .WRITE(RAM_WRITE)) ;

  // L'instance du processeur
  processeur u_proc(.clk(clk), .reset_n(reset_n),  .ADDR(RAM_ADDR), .DIN(RAM_DOUT), .DOUT(RAM_DIN), .WRITE(RAM_WRITE)) ;

  // Pour le moment la sortie LedBar n'est pas utilisée
  // Mais il faut affecter qqchose a la sortie
  // sinon "le module board" est éliminé par la synthèse
  always@( *) LedBar <= RAM_ADDR ;
endmodule


/////////////////////////////////////////////////////////////////////////////////////
// Code squelette pour le Nanoprocesseur: La mémoire pour le programme et les données
/////////////////////////////////////////////////////////////////////////////////////
`ifndef INSTRUCTIONS
// Etape 1
localparam ADD = 8'b0000_0100;
localparam SUB = 8'b0000_0110;
// Etape 1,2 & 3
localparam XOR = 8'b0000_0001;
localparam AND = 8'b0000_0010;
localparam  OR = 8'b0000_0011;
localparam LDA = 8'b0000_1010;
localparam STA = 8'b0000_1011;
// Etape 4
localparam NOP = 8'b0000_0000;
localparam OUT = 8'b0000_1100;
localparam ADC = 8'b0000_0101;
localparam SBC = 8'b0000_0111;
localparam ROL = 8'b0000_1000;
localparam ROR = 8'b0000_1001;
localparam JMP = 8'b0000_1101;
localparam JNC = 8'b0000_1110;
localparam JNZ = 8'b0000_1111;
`define INSTRUCTIONS
`endif


////////////////////////////////////////////////////////////////////////////////////////////
// La mémoire RAM.  Contenant un programme de test
////////////////////////////////////////////////////////////////////////////////////////////
// Attention le style de codage utilisé ici, ne fait pas partie des apprentissages
// d'ELECINF102.
// - Il suffit de comprendre que la RAM a un certain contenu initial

module ram (input logic [7:0] ADDR,
           input logic [7:0] D,
           output logic [7:0]Q,
           input logic clk,
           input logic WRITE );

  logic [7:0] memoire [0:255] ;

  // Le programme a éxécuter est ici
  // Programme pour l'étape 3
  initial begin
        memoire[0] = LDA  ;    memoire[1] = 8'h64 ;       // Accu = 3
        memoire[2] = ADD  ;    memoire[3] = 8'h65 ;       // Accu = 7
        memoire[4] = SUB  ;    memoire[5] = 8'h66 ;       // Accu = 6
        memoire[6] = XOR  ;    memoire[7] = 8'h67 ;       // Accu = 5
        memoire[8] = AND  ;    memoire[9] = 8'h68 ;       // Accu = 1
        memoire[10] = OR  ;    memoire[11] = 8'h69 ;      // Accu = 13
        memoire[12] = STA  ;   memoire[13] = 8'h6A ;      // Sauvegarde a l'adresse 106 (8'h6A)
        // Zone de données
        memoire[100] = 8'd3 ;  // @8'h64
        memoire[101] = 8'd4 ;  // @8'h65
        memoire[102] = 8'd1 ;  // @8'h66
        memoire[103] = 8'd3 ;  // @8'h67
        memoire[104] = 8'd11;  // @8'h68
        memoire[105] = 8'd12;  // @8'h69
  end

  always @(negedge clk)
    if(WRITE) memoire[ADDR] <= D ;

  always @(negedge clk)
    Q <= memoire[ADDR] ;
endmodule

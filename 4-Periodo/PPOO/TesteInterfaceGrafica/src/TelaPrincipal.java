import javax.swing.JButton;
import javax.swing.JFrame;

import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class TelaPrincipal{
    private JFrame janela;
    private JButton botao;
    private JButton botao2;

    public TelaPrincipal() {
        janela = new JFrame("Telinha");

        janela.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        janela.setSize(300, 400);

        janela.setLayout(new FlowLayout());

        criarComponentes();
    }

    private void criarComponentes(){
        botao = new JButton("Gerar acao");
        botao2 = new JButton("Botao2");

        botao.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                
            }
        });
        AcaoBotao acaoBotao = new AcaoBotao();
        botao2.addActionListener(acaoBotao);

        janela.add(botao);
        janela.add(botao2);
    }

    public void exibir(){
        janela.setVisible(true);
    }

    private class AcaoBotao implements ActionListener{

        @Override
        public void actionPerformed(ActionEvent e) {
            System.out.println("Gerou clique");
        }
    }

    private class AcaoBotao2 implements ActionListener{

        @Override
        public void actionPerformed(ActionEvent e) {
            System.out.println("Gerou clique");
        }
    }
}
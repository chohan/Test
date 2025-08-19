package test;

import java.awt.BorderLayout;
import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.JTextPane;
import javax.swing.JLabel;
import javax.swing.JButton;

public class TestWindowBuilder extends JFrame {

	private JPanel contentPane;

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					TestWindowBuilder frame = new TestWindowBuilder();
					frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Create the frame.
	 */
	public TestWindowBuilder() {
		setTitle("Operator login");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 350, 220);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(null);
		
		JLabel lblOperatorId = new JLabel("Operator ID");
		lblOperatorId.setBounds(10, 24, 58, 20);
		contentPane.add(lblOperatorId);
		
		JTextPane textPane_id = new JTextPane();
		textPane_id.setBounds(113, 24, 172, 20);
		contentPane.add(textPane_id);
		
		JLabel lblOperatorPassword = new JLabel("Operator password");
		lblOperatorPassword.setBounds(10, 55, 93, 20);
		contentPane.add(lblOperatorPassword);
		
		JTextPane textPane_password = new JTextPane();
		textPane_password.setBounds(113, 55, 172, 20);
		contentPane.add(textPane_password);
		
		JButton btnSubmit = new JButton("Submit");
		btnSubmit.setBounds(212, 120, 73, 23);
		contentPane.add(btnSubmit);
		
		JButton btnCancel = new JButton("Cancel");
		btnCancel.setBounds(113, 120, 73, 23);
		contentPane.add(btnCancel);
	}
}

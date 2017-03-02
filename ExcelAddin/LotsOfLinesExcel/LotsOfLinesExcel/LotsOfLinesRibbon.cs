using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Office.Tools.Ribbon;
using Excel = Microsoft.Office.Interop.Excel;
using Office = Microsoft.Office.Core;
using Microsoft.Office.Tools.Excel;
using System.Windows.Forms;
using System.IO;

namespace LotsOfLinesExcel
{
    public partial class LotsOfLinesRibbon
    {
        private void LotsOfLinesRibbon_Load(object sender, RibbonUIEventArgs e)
        {
            this.openInLotsOfLinesButton.Click += OpenInLotsOfLinesButton_Click;
        }

        private Dictionary<int, string> tempFileMap = new Dictionary<int, string>();

        private void OpenInLotsOfLinesButton_Click(object sender, RibbonControlEventArgs e)
        {
            //Create temp CSV file
            string tempPath = System.IO.Path.GetTempPath();
            string tempFile = tempPath + Guid.NewGuid().ToString() + ".csv";
            File.Create(tempFile);
            Globals.ThisAddIn.Application.ActiveWorkbook.SaveCopyAs(tempFile);

            //Open Lots of Lines application
            string lotsOfLinesDir = Environment.GetEnvironmentVariable("LOTS_OF_LINES_PATH");
            string lotsOfLinesFilename = lotsOfLinesDir + "\\LotsOfLinesApp.exe";
            try
            {
                System.Diagnostics.Process proc = System.Diagnostics.Process.Start(lotsOfLinesFilename, tempFile);
                tempFileMap[proc.Id] = tempFile;
                proc.Exited += Proc_Exited;
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Error loading Lots of Lines");
            }

            Excel.Workbook workbook = Globals.ThisAddIn.Application.ActiveWorkbook;
        }

        private void Proc_Exited(object sender, EventArgs e)
        {
            string tempFile = tempFileMap[((System.Diagnostics.Process)sender).Id];
            try
            {
                File.Delete(tempFile);
            }
            catch (Exception ex)
            {
                Console.Out.WriteLine(ex.Message);
            }
        }
    }
}

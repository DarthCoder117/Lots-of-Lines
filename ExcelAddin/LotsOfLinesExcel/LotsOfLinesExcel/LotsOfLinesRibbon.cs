using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Office.Tools.Ribbon;
using Excel = Microsoft.Office.Interop.Excel;
using Office = Microsoft.Office.Core;
using Microsoft.Office.Tools.Excel;

namespace LotsOfLinesExcel
{
    public partial class LotsOfLinesRibbon
    {
        private void LotsOfLinesRibbon_Load(object sender, RibbonUIEventArgs e)
        {
            this.openInLotsOfLinesButton.Click += OpenInLotsOfLinesButton_Click;
        }

        private void OpenInLotsOfLinesButton_Click(object sender, RibbonControlEventArgs e)
        {
            string lotsOfLinesDir = Environment.GetEnvironmentVariable("LOTS_OF_LINES_PATH");
            string lotsOfLinesFilename = lotsOfLinesDir + "\\LotsOfLinesApp.exe";
            System.Diagnostics.Process.Start(lotsOfLinesFilename);

            Excel.Workbook workbook = Globals.ThisAddIn.Application.ActiveWorkbook;
        }
    }
}
